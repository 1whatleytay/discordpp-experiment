#include <utility/data.h>

namespace utility {
    size_t Reader::sizeLeft() const {
        return size - index;
    }

    Reader::Reader(const uint8_t *data, size_t size) : data(data), size(size) { }

//    Reader::~Reader() {
//        if (size != index)
//            assert(false);
//    }

    void Writer::append(const Writer &serializer) {
        data.insert(data.end(), serializer.data.begin(), serializer.data.end());
    }

    const uint8_t *Writer::getData() const {
        return data.data();
    }

    size_t Writer::getSize() const {
        return data.size();
    }
}