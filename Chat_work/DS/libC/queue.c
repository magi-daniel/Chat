#include <stdlib.h>

#include "queue.h"

#define TRUE 1
#define FALSE 0

struct Queue
{
    void**   m_que;
    size_t m_size;
    size_t m_head;      /* Index of head in m_que. */
    size_t m_tail;      /* Index of tail in m_que. */
    size_t m_nItems;
};

/*help func*/
QueueResult CheakParameterInsert(const Queue *_queue, void* _item);
QueueResult CheakParameterRemove(const Queue *_queue, void**_item);
QueueResult QueueGet(const Queue* _queue, size_t _index, void** _pValue);


Queue* QueueCreate(size_t _size)
{
	void *ptr=NULL;
	Queue *ptrQueue=NULL;
	if(0 == _size)
	{
		return NULL;
	}
	ptrQueue=(Queue*)malloc(sizeof(Queue));
	if(ptrQueue == NULL)
	{
		return NULL;
	}
	ptr=(void**)malloc(_size*sizeof(void*));	
	if(ptr == NULL)
	{
		free(ptrQueue);
		return NULL;
	}

	ptrQueue -> m_que= ptr;
    ptrQueue -> m_size= _size;
    ptrQueue -> m_head=0;    
    ptrQueue -> m_tail=0;      
    ptrQueue -> m_nItems=0;
	
	return ptrQueue;
}



void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t i;
	if(_queue != NULL && *_queue != NULL )
	{
		if((*_queue)->m_que != NULL)
		{
			if(*_itemDestroy != NULL)
			{
				for(i=0; i< ((*_queue)->m_nItems); ++i)
				{
					(*_itemDestroy)((*_queue)->m_que[i]);
				}
			}
			free((*_queue)->m_que);
			free(*_queue);
			*_queue=NULL;
		}
	}
	else
	{
		_queue=NULL;	
	}
}



QueueResult QueueInsert(Queue* _queue,void* _item)
{
	QueueResult result;
	if((result =CheakParameterInsert(_queue, _item)) != QUEUE_SUCCESS)
	{
		return result;
	}
	(_queue -> m_que)[(_queue -> m_tail)]=_item; 
	(_queue -> m_tail)=((_queue -> m_tail)+1)%(_queue -> m_size);
	(_queue -> m_nItems)++;
	return QUEUE_SUCCESS;
}


QueueResult QueueRemove(Queue* _queue,void** _item)
{
	QueueResult result;
	if((result = CheakParameterRemove(_queue, _item)) != QUEUE_SUCCESS)
	{
		return  result;
	}
	*_item=(_queue->m_que)[_queue->m_head];
	(_queue -> m_nItems)--;
	(_queue -> m_head)=((_queue -> m_head)+1)%(_queue -> m_size);
	return QUEUE_SUCCESS;
}




size_t QueueIsEmpty(Queue* _queue)
{	
	if (NULL != _queue)
	{
		if (0 == (_queue -> m_nItems))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}


size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	void* element;
	size_t i,indexQueue;
	if (_queue == NULL)
	{
		return FALSE;
	}
	indexQueue=_queue->m_head;
	for (i = 0; i< _queue->m_nItems; ++i)
	{
		QueueGet(_queue,indexQueue,&element);
		if ( _action(element, _context)==0 )	
		{
			break;
		}
		indexQueue=(indexQueue+1)%(_queue->m_size);
	}
	/*putchar('\n');*/
	return i;
}



/**************help func***************/

QueueResult CheakParameterInsert(const Queue *_queue, void* _item)
{
	if((NULL == _queue) || (NULL == (_queue -> m_que)) || _item == NULL)
	{
		return QUEUE_NOT_INITIALIZED_ERROR;
	}
	if( (_queue -> m_nItems) == (_queue -> m_size))
	{
		return QUEUE_OVERFLOW_ERROR;
	}
	return QUEUE_SUCCESS;
}


QueueResult CheakParameterRemove(const Queue *_queue, void**_item)
{
	if((NULL == _queue) || (NULL == (_queue -> m_que)) || (NULL == _item) )
	{
		return QUEUE_NOT_INITIALIZED_ERROR;
	}
	
	if((_queue -> m_tail) == (_queue -> m_head) && 0 == (_queue -> m_nItems) )
	{
		return QUEUE_UNDERFLOW_ERROR;
	}
	return QUEUE_SUCCESS;
}


QueueResult QueueGet(const Queue* _queue, size_t _index, void** _pValue)
{
	*_pValue=(_queue->m_que)[_index];
	return QUEUE_SUCCESS;
}








