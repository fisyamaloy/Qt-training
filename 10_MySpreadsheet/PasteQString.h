#ifndef PASTEQSTRING_H
#define PASTEQSTRING_H

#include <QString>
#include <cstdint>

class PasteQString
{
public:
    enum class Operation : std::uint8_t
    {
        CUT,
        COPY
    };

    void setBuffer(const QString& buf, const Operation o)
    {
        buffer = std::move(buf);
        op = o;
    }

    QString getBuffer()
    {
        if (op == Operation::CUT)
        {
            QString buf = std::move(buffer);
            buffer = "";
            return buf;
        }
        else
        {
            return buffer;
        }
    }

    const QString& lookAtBuffer() const
    {
        return buffer;
    }

    Operation getOperation() const
    {
        return op;
    }

private:
    QString buffer;
    Operation op;
};

#endif // PASTEQSTRING_H
