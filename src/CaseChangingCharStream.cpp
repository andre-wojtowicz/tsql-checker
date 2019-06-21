#include "CaseChangingCharStream.h"

#include "antlr4-runtime.h"

CaseChangingCharStream::CaseChangingCharStream(antlr4::CharStream *stream, bool upper)
{
    this->stream = stream;
    this->upper = upper;
}

size_t CaseChangingCharStream::index()
{
	return stream->index();
}

size_t CaseChangingCharStream::size()
{
    return stream->size();
}

std::string CaseChangingCharStream::getSourceName() const
{
    return stream->getSourceName();
}

void CaseChangingCharStream::consume()
{
    stream->consume();
}

std::string CaseChangingCharStream::getText(const antlr4::misc::Interval &interval)
{
    return stream->getText(interval);
}

std::string CaseChangingCharStream::toString() const
{
	return "";
}

size_t CaseChangingCharStream::LA(ssize_t i)
{	
    size_t c = stream->LA(i);

    if (c <= 0)
    {
        return c;
    }
#ifdef _WIN64
    if (upper)
    {
        return size_t(toupper(int(c)));
    }

    return size_t(tolower(int(c)));
#endif
#ifndef _WIN64
    char o = char(c);

    if (upper)
    {
        return size_t(toupper(o));
    }

    return size_t(tolower(o));
#endif
}

ssize_t CaseChangingCharStream::mark()
{
    return stream->mark();
}

void CaseChangingCharStream::release(ssize_t marker)
{
    stream->release(marker);
}

void CaseChangingCharStream::seek(size_t index)
{
    stream->seek(index);
}