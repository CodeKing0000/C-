#include <iostream>

// enum class MirrorType {
//  Vertical,
//  Horizontal
// }

class Image {

    int rows;
    int cols;
    int channels;
    unsigned char* data;
    int ref_count;

public:
    Image(int rows, int cols, int channels, unsigned char* data, int ref_count);

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image(const Image& image) {
        this->rows = image.rows;
        this->cols = image.cols;
        this->channels = image.channels;
        this->data = image.data;
        this->ref_count = image.ref_count;
        (*this->ref_count)++;
    };

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& operator=(const Image& image) {
        if(this == &image) {
            return *this;
        }

        if(this->ref_count != nullptr) {
        (*this->ref_count)--;

            if(this->ref_count == 0) {
                delete this->rows;
                delete this->cols;
                delete this->channels;
                delete this->data;
                delete this->ref_count;
            }
        }
        
        this->rows = image.rows;
        this->cols = image.cols;
        this->channels = image.channels;
        this->data = image.data;
        this->ref_count = image.ref_count;

        (*this->ref_count)++;
    };

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image clone() {
        Image *this = Image clone;
        (this->ref_count)++;
        return clone;
    };

    //Скопировать изображение.
    void copyTo(Image& image) {
        Image *this = Image clone;
        (this->ref_count)++; 
    };

    void create(int obj_rows, int obj_cols, int obj_channels, unsigned char* obj_data, int obj_ref_count) {
        rows = obj_rows;
        cols = obj_cols;
        channels = obj_channels;
        data = obj_data;
        ref_count = obj_ref_count;
    };

    bool empty() {
        delete this->rows;
        delete this->cols;
        delete this->channels;
        delete this->data;
        delete this->ref_count;
    };

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release() {
        if(this->ref_count != nullptr && ref_count > 1) {
        (*this->ref_count)--;
        }
        delete this->rows;
        delete this->cols;
        delete this->channels;
        delete this->data;
        delete this->ref_count;

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
        return const data;
    };
    unsigned char* data() {
        return this->data;
    };
    int rows() {
        return this->rows;
    };
    int cols() {
        return this->cols;
    };
    int total() {
        return this->rows, this->cols, this->channels, this->data, this->ref_count;
    };
    int channels() {
        return this->channels;
    };

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index) {
        if(index < 0 || index > 255) {
            throw std::out_of_range;
        }

        return this->data[index];
    };
    const unsigned char& at(int index) const {
        if(index < 0 || index > 255) {
            throw std::out_of_range;
        }

        return const this->data[index];
    };

//создает новое изображение, которое инициализируется нулями.
    Image zeros(int rows, int cols, int channels) {
        Image a(this->rows, this->cols, this->channels, (0, 0), this->ref_count);
        return a;
    };

//создает новое изображение, которое инициализируется значением value.
    Image values(int rows, int cols, int channels, unsigned char value) {
        Image a(this->rows, this->cols, this->channels, value, 0);
        return a;
    };

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type) {
        if(type = 'Vertical') {
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
        }
        if(type = 'Horizontal') {
            int rowSize = this->cols * channels;
            unsigned char* tempRow = new unsigned char[rowSize];

            for (int y = 0; y < this->rows / 2; ++y) {
                unsigned char* rowTop = &data[y * rowSize];
                unsigned char* rowBottom = &data[(this->rows - 1 - y) * rowSize];
                std::swap_ranges(rowTop, rowTop + rowSize, rowBottom);
            }
    };

    //Повернуть на угол кратный 90
    void Rotate(double angle) {
        int count = angle / 90;
        while(count > 0) {
            this->rows = a;
            this->rows = this->cols;
            this->cols = a;
            count--;
        }
    };

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef(std::string obj) {
        return obj.ref_count;
    };
};