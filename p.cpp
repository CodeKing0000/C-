#include <iostream>
#include <string>
#include <stdexcept>
#include "head.hpp"

    Image::Image(int rows, int cols, int channels, unsigned char* data, int ref_count) {};

    bool Image::operator<(const Image& other) const {
        if (rows != other.rows) {
            return rows < other.rows;
        };
        if (cols != other.cols) {
            return cols < other.cols;
        };
        if (channels != other.channels) {
            return channels < other.channels;
        };
        return data < other.data;
    };
    bool operator>(const Image& other) const {
        if (rows != other.rows) {
            return rows > other.rows;
        };
        if (cols != other.cols) {
            return cols > other.cols;
        };
        if (channels != other.channels) {
            return channels > other.channels;
        };
        return data > other.data;
    };
    bool operator<=(const Image& other) const {
        if (rows != other.rows) {
            return rows <= other.rows;
        };
        if (cols != other.cols) {
            return cols <= other.cols;
        };
        if (channels != other.channels) {
            return channels <= other.channels;
        };
        return data <= other.data;
    };
    bool operator>=(const Image& other) const {
        if (rows != other.rows) {
            return rows >= other.rows;
        };
        if (cols != other.cols) {
            return cols >= other.cols;
        };
        if (channels != other.channels) {
            return channels >= other.channels;
        };
        return data >= other.data;
    };
    bool operator==(const Image& other) const {
        return rows == other.rows && cols == other.cols && data == other.data && channels == other.channels;
    };

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image(const Image& image) {
        rows = image.rows;
        cols = image.cols;
        channels = image.channels;
        data = image.data;
        ref_count = image.ref_count;
        (ref_count)++;
    };

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& operator=(const Image& image) {
        if(*this == image) {
            return *this;
        }

        if(ref_count != 0) {
        (ref_count)--;

            if(ref_count == 0) {
                rows = 0;
                cols = 0;
                channels = 0;
                data = 0;
                ref_count = 0;
            }
        }
        
        rows = image.rows;
        cols = image.cols;
        channels = image.channels;
        data = image.data;
        ref_count = image.ref_count;

        (ref_count)++;
    };

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image clone() {
        Image clone = *this;
        (ref_count)++;
        return clone;
    };

    //Скопировать изображение.
    void copyTo(Image& image) {
        Image clone = *this;
        (ref_count)++; 
    };

    void create(int obj_rows, int obj_cols, int obj_channels, unsigned char* obj_data, int obj_ref_count) {
        rows = obj_rows;
        cols = obj_cols;
        channels = obj_channels;
        data = obj_data;
        ref_count = obj_ref_count;
    };

    bool empty() {
        if(rows == 0, cols == 0, channels == 0, data == 0) {
            return true;
        }
        return false;
    };

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release() {
        if(ref_count != 0 && ref_count > 1) {
        (ref_count)--;
        }
            rows = 0;
            cols = 0;
            channels = 0;
            data = 0;
            ref_count = 0;

    };

//возвращает новое изображение, которое содержит один столбец по индексу x.
    Image col(int x) {
        this->cols = 1;
    };

//аналог метода col(int x) для строк.
    Image row(int y) {
        this->rows = 1;
    };

    const unsigned char* data() const {
        return data;
    };
    unsigned char* data() {
        return data;
    };
    int rows() {
        return rows;
    };
    int cols() {
        return cols;
    };
    int total() {
        return rows, cols, channels, data, ref_count;
    };
    int channels() {
        return channels;
    };

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index) {
        if(index < 0 || index > 255) {
            throw std::out_of_range("Unsigned char& at(int index) > 255 or < 0");
        }

        return data[index];
    };
    const unsigned char& at(int index) const {
        if(index < 0 || index > 255) {
            throw std::out_of_range("Const unsigned char& at(int index) const > 255 or < 0");
        }

        return data[index];
    };

//создает новое изображение, которое инициализируется нулями.
    Image zeros(int rows, int cols, int channels) {
        Image a(rows, cols, channels, 0, 0);
        return a;
    };

//создает новое изображение, которое инициализируется значением value.
    Image values(int rows, int cols, int channels, unsigned char* value) {
        Image a(rows, cols, channels, value, 0);
        return a;
    };

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type) {
        if(type == MirrorType::Vertical) {
            for (int y = 0; y < this->rows; ++y) {
                for (int x = 0; x < this->cols / 2; ++x) {
                    int x1 = (y * this->cols + x) * this->channels;
                    int x2 = (y * this->cols + (this->cols - 1 - x)) * this->channels;
                    for (int c = 0; c < channels; ++c) {
                        unsigned char temp = data[x1 + c];
                        data[x1 + c] = data[x2 + c];
                        data[x2 + c] = temp;
                    }
                }
            }
        };
        if(type == MirrorType::Horizontal) {
            int rowSize = this->cols * channels;
            unsigned char* tempRow = new unsigned char[rowSize];

            for (int y = 0; y < this->rows / 2; ++y) {
                unsigned char* rowTop = &data[y * rowSize];
                unsigned char* rowBottom = &data[(this->rows - 1 - y) * rowSize];
                std::swap_ranges(rowTop, rowTop + rowSize, rowBottom);
            }
        };
    };
    //Повернуть на угол кратный 90
    void Rotate(double angle) {
        int count = angle / 90;
        while(count > 0) {
            int a = rows;
            rows = cols;
            cols = a;
            count--;
        }
    };

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef() {
        return ref_count;
    };

};