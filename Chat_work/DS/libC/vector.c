/*#include <stdio.h>*/
#include <stdlib.h>

#include "vector.h"

#define FALSE 0
#define  TRUE 1


struct Vector
{
    void**    m_items;
    size_t  m_originalSize;   /* _initialCapacity original allocated space for items)*/
    size_t  m_size;           	    /* actual allocated space for items)*/
    size_t  m_nItems;     	    /* actual number of items */
    size_t  m_blockSize;	   /* the chunk size to be allocated when no space*/
};



Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
	void *ptr=NULL;
	Vector *ptrVector=NULL;
	if((_initialCapacity == 0) && (_blockSize == 0))
	{
		return NULL;
	}
	ptrVector=(Vector*)malloc(sizeof(Vector));
	if(ptrVector == NULL)
	{
		return NULL;
	}
	ptr=(void**)malloc(_initialCapacity*sizeof(void*));	
	if(ptr == NULL)
	{
		free(ptrVector);
		return NULL;
	}
	ptrVector -> m_items=ptr;
	ptrVector -> m_originalSize=_initialCapacity;
	ptrVector -> m_size=_initialCapacity;
	ptrVector -> m_nItems=0;
	ptrVector -> m_blockSize=_blockSize;
	return ptrVector;
}



void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	size_t i;
	if (_vector != NULL && *_vector != NULL)
	{
		if ((*_elementDestroy) != NULL)
		{
			for(i=0; i < ((*_vector)->m_nItems); i++)
			{
				
				(*_elementDestroy)((*_vector)->m_items[i]);
			}
		}
		free((*_vector)->m_items);
		free(*_vector);
		*_vector=NULL;		
	}
	else
	{
		_vector=NULL;
	}
}





VectorResult cheakParameter(Vector *_vector, void* _item)
{
	if(_vector == NULL || (_vector->m_items == NULL) || _item == NULL)
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
	if((_vector->m_size) == 0)
	{
		return VECTOR_GENERAL;
	}
	if((_vector->m_size) < (_vector->m_nItems))
	{
		return VECTOR_GENERAL;
	}
	return VECTOR_SUCCESS;
}

VectorResult increase(Vector *_vector)
{
	void* temp=NULL;
	if(_vector == NULL)
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
	if((_vector->m_blockSize) == 0)
	{
		return VECTOR_OVERFLOW;
	}
	/*realloc*/
	temp=realloc((_vector->m_items),((_vector->m_size)+(_vector->m_blockSize))*(sizeof(void*)));
	/*cheak realloc*/
	if(temp == NULL)
	{
		return VECTOR_REALLOCATION_FAILED;
	}
	(_vector->m_size)=((_vector->m_size)+(_vector->m_blockSize));
	(_vector->m_items)=temp;
	return VECTOR_SUCCESS;
}


VectorResult VectorAppend(Vector* _vector, void* _item)
{
	VectorResult result;
	if((result = cheakParameter(_vector, _item)) != VECTOR_SUCCESS)
	{
		return result;		
	}
	if((_vector->m_size) == (_vector->m_nItems))
	{
		if((result = increase(_vector)) != VECTOR_SUCCESS)
		{
			return result;
		}
	}
	(_vector->m_items)[_vector->m_nItems]= _item;
	(_vector->m_nItems)++;
	return VECTOR_SUCCESS;
}


VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	void* temp=NULL;
	VectorResult result;
	
	if((_vector == NULL) || (_vector -> m_items == NULL) )
	{
		return VECTOR_NOT_INITIALIZED_ERROR; 
	}
	if(_pValue == NULL || *_pValue == NULL)
	{
		return VECTOR_NOT_INITIALIZED_ERROR; 
	}
	if((_vector -> m_nItems) == 0)
	{
		return VECTOR_UNDERFLOW; 
	}
	
 	*_pValue=(_vector -> m_items)[(_vector -> m_nItems)-1];
	(_vector -> m_nItems)--;
	if((_vector -> m_size)-(_vector -> m_nItems) >= (2*(_vector -> m_blockSize)))
	{
		if((_vector->m_size)-(_vector->m_blockSize) >= (_vector->m_originalSize) )
		{
			/*realloc*/
			temp=realloc((_vector->m_items),((_vector->m_size)-(_vector->m_blockSize))*(sizeof(void*)));
			/*cheak realloc*/
			if(temp != NULL)
			{
				(_vector -> m_size)=((_vector -> m_size)-(_vector -> m_blockSize));
				(_vector -> m_items)=temp;	
				return VECTOR_SUCCESS; 
			}
		}
	}
	return VECTOR_SUCCESS; 
}


VectorResult cheakPrameterGet(const Vector *_vector, size_t _index, void** _pValue)
{	
	if((_vector == NULL) || (_vector -> m_items == NULL))
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
	if (_pValue == NULL)
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
 	if(_index >= (_vector -> m_nItems) )
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	VectorResult result;
	if(result=(cheakPrameterGet(_vector, _index, _pValue)) != VECTOR_SUCCESS)
	{
		return result;
	}
	*_pValue=(_vector->m_items)[_index];
	return VECTOR_SUCCESS;
}



VectorResult cheakPrameterSet(Vector *_vector, size_t _index, void*  _value)
{	
	if((_vector == NULL) || (_vector -> m_items == NULL))
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
	if(_value == NULL)
	{
		return VECTOR_NOT_INITIALIZED_ERROR;
	}
 	if(_index >= (_vector -> m_nItems) )
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	VectorResult result;
	if(result=(cheakPrameterSet(_vector,_index,_value)) != VECTOR_SUCCESS)
	{
		return result;
	}
	(_vector -> m_items)[_index]=_value;
	return VECTOR_SUCCESS;
}


size_t VectorSize(const Vector* _vector)
{
	if((_vector == NULL) || (_vector -> m_items == NULL))
	{
		return FALSE;
	}
	
	return (_vector -> m_nItems);	
}

size_t VectorCapacity(const Vector* _vector)
{
	if(_vector == NULL)
	{
		return FALSE;
	}
	return (_vector -> m_size);	
	
}


/********************TODO************************/


size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	void* elem ;
	size_t i;
	if(_vector == NULL)
	{
		return FALSE;
	}
	for(i = 0; i < VectorSize(_vector); ++i)
	{
		VectorGet(_vector, i, &elem);
		if(_action(elem, i, _context) == 0)
		{
			break;
		}	
	}
	/*putchar('\n');*/
	return i;
}




/*int (*VectorElementAction)(void* _element, size_t _index, void* _context)*/




/********************************************/
/*




void VectorPrint(Vector *_vector)
{
	size_t i;
	ADTErr result;
	if((result = cheakParameter(_vector)) == ERR_OK)
	{
		if((_vector -> m_nItems) > 0)
		{
			for(i=0; i<(_vector -> m_nItems) ;i++ )
			{
				printf("%d ", (_vector -> m_items[i]));
			}
			printf("\n");
		}
	}
}








ADTErr getMagicNum(Vector *_vector, size_t*  _magicNum)
{
	(*_magicNum)=(_vector -> m_magicNum);	
	return ERR_OK;
}


*/


