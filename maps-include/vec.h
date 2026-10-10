#pragma once
#include <cstdint>

#include "libllcd.h"

template <typename T, uint32_t MaxSize>
class Vector {
private:
    T data[MaxSize];
    uint32_t v_size;

public:
    _LIBLLCD_DEVICE_VISIBILITY
    Vector() : v_size(0) {}
    _LIBLLCD_DEVICE_VISIBILITY
    ~Vector() {}

    /*
    Vector(std::initializer_list<T> init) : v_size(init.size()) {
    	assert(v_size <= MaxSize);
    	uint32_t index = 0;
    	for (const T& value : init) {
    		data[index++] = value;
    	}
    }
    */

    //use array to initialize
    _LIBLLCD_DEVICE_VISIBILITY
    Vector(const T *arr, uint32_t size) : v_size(size) {
        for (uint32_t i = 0; i < v_size && v_size <= MaxSize; i++) {
            data[i] = arr[i];
        }
    }

    _LIBLLCD_DEVICE_VISIBILITY
    void push_back(const T *values, uint32_t count) {
    	for (uint32_t i = 0; i < count && v_size < MaxSize; i++) {
    		data[v_size++] = values[i];
    	}
    }

    _LIBLLCD_DEVICE_VISIBILITY
    void push_back(const T &value) {
        if (v_size < MaxSize) {
        	data[v_size++] = value;
        } else {
        	printf("Vector reached MAXSIZE=%d, %s:%d\n", MaxSize, __FILE__, __LINE__);
        }
    }

    _LIBLLCD_DEVICE_VISIBILITY
    T& operator[](uint32_t index) {
        if (index < v_size) {
        	return data[index];
        } else {
        	printf("Error: Vector index exceed v_size=%d, %s:%d\n", v_size, __FILE__, __LINE__);
        	return data[v_size-1];
        }
    }

    _LIBLLCD_DEVICE_VISIBILITY
    // Const version of the subscript operator for read-only access
    const T& operator[](uint32_t index) const {
        if (index < v_size) {
        	return data[index];
        } else {
        	printf("Error: Vector index exceed v_size=%d, %s:%d\n", v_size, __FILE__, __LINE__);
        	return data[v_size-1];
        }
    }

    _LIBLLCD_DEVICE_VISIBILITY
    Vector& operator=(const Vector& other) {
    	if (other.v_size <= MaxSize) {
    		if(this != &other) {
    			v_size = other.v_size;
    			for (uint32_t i = 0; i < v_size; i++ ) {
    				data[i] = other.data[i];
    			}
    		}
    		return *this;
    	} else {
    		printf("Error: Reference Vector v_size=%d exceed MAXSIZE=%d, %s:%d\n", other.v_size, MaxSize, __FILE__, __LINE__);
    		return *this;
    	}
    }

    _LIBLLCD_DEVICE_VISIBILITY
    uint32_t size() const {
        return v_size;
    }

    _LIBLLCD_DEVICE_VISIBILITY
    bool empty() const {
    	return v_size == 0;
    }

    _LIBLLCD_DEVICE_VISIBILITY
    void clear() {
    	v_size = 0;
    }
};

typedef Vector<uint8_t, 33> ApcVector;
typedef Vector<uint8_t, 4> DmVector;
typedef Vector<uint8_t, 8> PkgVector;
