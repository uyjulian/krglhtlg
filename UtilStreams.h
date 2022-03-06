
#pragma once

// Trimmed tTVPMemoryStream for the TLG6 encoder.
class tTVPMemoryStream
{
protected:
	void * Block;
	tjs_uint Size;
	tjs_uint AllocSize;
	tjs_uint CurrentPos;

public:
	tTVPMemoryStream()
	{
		Init();
	}

	virtual ~tTVPMemoryStream()
	{
		if(Block) Free(Block);
	}

	tjs_uint Write(const void *buffer, tjs_uint write_size)
	{
		// writing may increase the internal buffer size.

		tjs_uint newpos = CurrentPos + write_size;
		if(newpos >= AllocSize)
		{
			// exceeds AllocSize
			tjs_uint onesize;
			if(AllocSize < 64*1024) onesize = 4*1024;
			else if(AllocSize < 512*1024) onesize = 16*1024;
			else if(AllocSize < 4096*1024) onesize = 256*1024;
			else onesize = 2024*1024;
			AllocSize += onesize;

			if(CurrentPos + write_size >= AllocSize) // still insufficient ?
			{
				AllocSize = CurrentPos + write_size;
			}

			Block = Realloc(Block, AllocSize);

			if(AllocSize && !Block)
				TVPThrowExceptionMessage(TJS_W("Cannot allocate memory"));
				// this exception cannot be repaird; a fatal error.
		}

		memcpy((tjs_uint8*)Block + CurrentPos, buffer, write_size);

		CurrentPos = newpos;

		if(CurrentPos > Size) Size = CurrentPos;

		return write_size;
	}

	// non-tTJSBinaryStream based methods
	void * GetInternalBuffer() const
	{
		return Block;
	}

	tjs_uint64 GetSize(void) const
	{
		return Size;
	}

	void Release(void)
	{
		delete this;
	}

protected:
	void Init()
	{
		Block = NULL;
		Size = 0;
		AllocSize = 0;
		CurrentPos = 0;
	}

protected:
	virtual void * Alloc(size_t size)
	{
		return malloc(size);
	}
	virtual void * Realloc(void *orgblock, size_t size)
	{
		return realloc(orgblock, size);
	}
	virtual void Free(void *block)
	{
		free(block);
	}
};
//---------------------------------------------------------------------------
