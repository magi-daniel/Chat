#include "list_itr.h"
#include "list.h"
#include "list_functions.h"
#include "HashMap.h"
#include <stdlib.h> /*size_t malloc free*/
#include <math.h> 

#define FALSE 0
#define TRUE 1
#define RELATIVE_INDEX(x) ((x) % _map->m_capacity)

typedef struct Data
{
    void* m_key;
    void* m_value;
} Data;

typedef struct DestroyFunctions
{
    void (*m_keyDestroy)(void* _key);
    void (*m_valueDestroy)(void* _value);
} DestroyFunctions;

typedef struct equalityContext
{
    EqualityFunction m_equality;
    void* m_key;
} equalityContext;

typedef struct ForEachContext
{
    KeyValueActionFunction m_function;
    void* m_context;
    size_t m_invokeTimes;
} ForEachContext;

struct HashMap
{
    List** m_data; /*the data inside each index*/
    HashFunction m_hashFunction; /*function to hash by*/
    EqualityFunction m_equalityFunction; /*function to compare by*/
    size_t m_numOfItems; /*the amount of items in the hashmap*/
    size_t m_size; /*original size given by the client*/
    size_t m_capacity; /*real hush size */
    size_t m_numberOfBuckets; /*amount of lists*/
    size_t m_maxChainLength; /*largest list*/
};

static ListItr Find(const HashMap* _map, const void* _key, void** _pKey,  void** _pValue, int _insToKey, int _insToVal);
static MapResult FindParaCheck(const HashMap* _map, const void* _key, void** _pValue);
static ListItr SearchInList(const HashMap* _map, const void* _key, size_t _index);
static void DestroyAllKeysAndValues(DestroyFunctions _destroy, HashMap* _map);
static MapResult InsertParaCheck(const HashMap* _map, const void* _key);
static MapResult CreateBucketIfNeeded(HashMap* _map, size_t _index);
static MapResult Insert(HashMap* _map, Data* _data, size_t index);
static int DestroyKeyAndValue(void* _element, void* _context);
static int ForEachData(void* _element, void* _context);
static Data* InitializeData(void* _key, void* _value);
static int FindByKey(void * _element, void* _context);
static size_t FindFirstPrime(size_t _checkedNumber);
static void DestroyData(void* _data);

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* map;
    /*check parametes legal*/
    if(0 == _capacity || NULL == _hashFunc || NULL == _keysEqualFunc)
    {
        return NULL;
    }

    map = (HashMap*)calloc(sizeof(HashMap), 1);
    if(NULL == map)
    {
        return NULL;
    }
    map->m_capacity = FindFirstPrime(_capacity);
    map->m_data = (List**)calloc(sizeof(List*), map->m_capacity);
    if(NULL == map->m_data)
    {
        free(map);
        return NULL;
    }
    /*initialize what's left*/
    map->m_equalityFunction = _keysEqualFunc;
    map->m_hashFunction = _hashFunc;
    map->m_size = _capacity;

    return map;
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    size_t i;
    DestroyFunctions destroy;

    if(NULL == _map || NULL == *_map)
    {
        return;
    }

    if(NULL != _keyDestroy || NULL != _valDestroy)
    {
        destroy.m_keyDestroy = _keyDestroy;
        destroy.m_valueDestroy = _valDestroy;
        DestroyAllKeysAndValues(destroy, *_map);
    }
    for(i = 0; i < (*_map)->m_capacity; ++i)
    {
        if(NULL != (*_map)->m_data[i])
        {
            ListDestroy(&((*_map)->m_data[i]), DestroyData);
        }
    }
    free((*_map)->m_data);
    free(*_map);
    *_map = NULL;
}

MapResult HashMapInsert(HashMap* _map, const void* _key, void* _value)
{
    MapResult check;
    size_t index;
    Data* data;

    if(MAP_SUCCESS != (check = InsertParaCheck(_map, _key)))
    {
        return check;
    }
    /*looks if key exists*/
    if(NULL != Find(_map, _key, NULL, NULL, FALSE, FALSE))
    {
        return MAP_KEY_DUPLICATE_ERROR;
    }
    index = RELATIVE_INDEX(_map->m_hashFunction(_key));
    if(MAP_SUCCESS != CreateBucketIfNeeded(_map, index))
    {
        return MAP_ALLOCATION_ERROR;
    }
    if (NULL == (data = InitializeData((void*)_key, _value)))
    {
        return MAP_ALLOCATION_ERROR; 
    }

    return Insert(_map, data, index);
}

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    MapResult check;
    ListItr foundData;
    Data* data;

    if(MAP_SUCCESS != (check = FindParaCheck(_map, _searchKey, _pValue)))
    {
        return check;
    }
    if (NULL == _pKey)
    {
        return MAP_KEY_NULL_ERROR;
    }

    foundData = Find(_map, _searchKey, _pKey, _pValue, TRUE, TRUE);
    if (NULL == foundData)
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    data = ListItrRemove(foundData);
    free(data);
    --(_map->m_numOfItems);

    return MAP_SUCCESS;
}

MapResult HashMapFind(const HashMap* _map, const void* _key, void** _pValue)
{
    MapResult check;

    if(MAP_SUCCESS != (check = FindParaCheck(_map, _key, _pValue)))
    {
        return check;
    }

    return (Find(_map, _key, NULL, _pValue, FALSE, TRUE) != NULL) ? MAP_SUCCESS : MAP_KEY_NOT_FOUND_ERROR ;
}

size_t HashMapSize(const HashMap* _map)
{
    if(NULL == _map)
    {
        return 0;
    }

    return _map->m_numOfItems;
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t i, count = 0;
    ForEachContext context;
    ListItr begin, end;

    if(NULL == _map || NULL == _action)
    {
        return 0;
    }
    context.m_function = _action;
    context.m_context = _context;
    context.m_invokeTimes = count;

    for(i = 0; i < _map->m_capacity; ++i)
    {
        if(NULL == _map->m_data[i])
        {
            continue;
        }
        begin = ListItrBegin(_map->m_data[i]);
        end = ListItrEnd(_map->m_data[i]);
        ListItrForEach(begin, end, ForEachData, &context);
    }

    return context.m_invokeTimes;
}

static int ForEachData(void* _element, void* _context)
{
    ForEachContext* context = _context;
    Data* data = _element;

    ++(context->m_invokeTimes);
    return context->m_function(data->m_key, data->m_value, context->m_context);
}

static ListItr Find(const HashMap* _map, const void* _key, void** _pKey,  void** _pValue, int _insToKey, int _insToVal)
{
    ListItr found;
    size_t index;
    Data* data;

    index = RELATIVE_INDEX(_map->m_hashFunction(_key));
    /*check if the list exists*/
    if(NULL ==_map->m_data[index])
    {
        return NULL;
    }
    /*looks for key in the list*/
    found = SearchInList(_map, _key, index);
    /*checks if found something*/
    if(found == NULL)
    {
        return NULL;
    }
    data = ListItrGet(found);
    if(_insToVal == TRUE)
    {
        *_pValue = data->m_value;
    }
    if(_insToKey == TRUE)
    {
        *_pKey = data->m_key;
    }
    
    return found;
}

static int FindByKey(void * _element, void* _context)
{
    return ((equalityContext*)_context)->m_equality(((equalityContext*)_context)->m_key, ((Data*)_element)->m_key);
}

static MapResult FindParaCheck(const HashMap* _map, const void* _key, void** _pValue)
{
    if(NULL == _map)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(NULL == _key || NULL == _pValue)
    {
        return MAP_KEY_NULL_ERROR;
    }

    return MAP_SUCCESS; 
}

static MapResult InsertParaCheck(const HashMap* _map, const void* _key)
{
    if(NULL == _map)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    if(NULL == _key)
    {
        return MAP_KEY_NULL_ERROR;
    }

    return MAP_SUCCESS; 
}

static size_t FindFirstPrime(size_t _checkedNumber)
{
    size_t square;
    size_t i;
    /* if 2 return 2*/
    if(2 == _checkedNumber || 1 == _checkedNumber)
    {
        return 2;
    }
    /*if number isn't odd ++ it */
    if(_checkedNumber % 2 == 0)
    {
        ++_checkedNumber;
    }
    while(TRUE)
    {
        /*if found that the number is not prime keep going from next number*/
        square = (size_t)(sqrt((double)_checkedNumber) + 1);
        for(i = 3; i < square; i += 2)
        {
            if (_checkedNumber % i == 0)
            {
                _checkedNumber += 2;
                break;
            }
        }
        if(i >= square)
        {
            break;
        }
    }

    return _checkedNumber;
}

static MapResult Insert(HashMap* _map, Data* _data, size_t index)
{
    size_t listSize;
    
    if(LIST_ALLOCATION_ERROR == ListPushTail(_map->m_data[index], _data))
    {
        return MAP_ALLOCATION_ERROR;
    }
    if ((listSize = ListSize(_map->m_data[index])) > _map->m_maxChainLength)
    {
        _map->m_maxChainLength =  listSize;
    }
    ++(_map->m_numOfItems);
    return MAP_SUCCESS;
}

static MapResult CreateBucketIfNeeded(HashMap* _map, size_t _index)
{
     if(NULL == _map->m_data[_index])
    {
        _map->m_data[_index] = ListCreate();
        if(NULL == _map->m_data[_index])
        {
            return MAP_ALLOCATION_ERROR;
        }
        ++(_map->m_numberOfBuckets);
    }
    return MAP_SUCCESS;
}

static Data* InitializeData(void* _key, void* _value)
{
    Data* data;

    data = (Data*) malloc(sizeof(Data));
    if (NULL == data)
    {
        return NULL; 
    }
    data->m_key = _key;
    data->m_value = _value;

    return data;
}

static ListItr SearchInList(const HashMap* _map, const void* _key, size_t _index)
{
    ListItr begin, end, found;
    equalityContext cont;

    begin = ListItrBegin(_map->m_data[_index]);
    end = ListItrEnd(_map->m_data[_index]);
    cont.m_key = (void*)_key;
    cont.m_equality = _map->m_equalityFunction;
    found = ListItrFindFirst(begin, end, FindByKey, &cont);
    
    return found == end ? NULL : found; 
}

static void DestroyAllKeysAndValues(DestroyFunctions _destroy, HashMap* _map)
{
    size_t i;
    ListItr begin;
    ListItr end;

    for(i = 0; i < _map->m_capacity; ++i)
    {
        if(_map->m_data[i] != NULL)
        {
            begin = ListItrBegin(_map->m_data[i]);
            end = ListItrEnd(_map->m_data[i]);
            ListItrForEach(begin, end, DestroyKeyAndValue, &_destroy);
        }
    }
}

static int DestroyKeyAndValue(void* _element, void* _context)
{
    DestroyFunctions* destroy = (DestroyFunctions*)_context;

    if(NULL != destroy->m_valueDestroy)
    {
        (destroy->m_valueDestroy)(((Data*)_element)->m_value);
    }
    if(NULL != destroy->m_keyDestroy)
    {
        (destroy->m_keyDestroy)(((Data*)_element)->m_key);
    }

    return 1;
}

static void DestroyData(void* _data)
{
    free((Data*)_data);
}
