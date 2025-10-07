# Бинарный поиск в массиве

## 1. Общая постановка задачи

Необходимо создать новый компонент для калькулятора, который должен
реализовывать новый интерфейс с методом определения элемента в массиве методом бинарного поиска. Интерфейс должен содержать методы с разными типами данных (int, float, double, long double).

## 2. Реализуемый алгоритм бинарного поиска.

Бинарный поиск — это очень быстрый и эффективный алгоритм для нахождения элемента в **отсортированном** массиве (или списке). 

> [!IMPORTANT]
Ключевое требование, без которого он не работает — **данные должны быть упорядочены**.

### Как он работает по шагам?

1. **Начало:** Алгоритм определяет границы поиска: в самом начале это весь массив (от первого до последнего элемента).
    
2. **Поиск середины:** Он находит средний элемент в текущих границах поиска.
    
3. **Сравнение:** Значение этого среднего элемента сравнивается с тем значением, которое мы ищем.
    
    - **Нашли!** Если средний элемент и есть искомый, поиск успешно завершен.
        
    - **Искомый элемент меньше.** Если искомый элемент меньше среднего, значит, он может находиться только в левой половине массива. Алгоритм отбрасывает правую половину и повторяет поиск, но уже в новых, суженных границах (от начала до элемента перед серединой).
        
    - **Искомый элемент больше.** Если искомый элемент больше среднего, он может быть только в правой половине. Алгоритм отбрасывает левую и продолжает поиск в правой части (от элемента после середины и до конца).
        
4. **Повторение:** Шаги 2 и 3 повторяются до тех пор, пока элемент не будет найден или пока границы поиска не "схлопнутся" (левая граница станет больше правой). Если границы сошлись, а элемент так и не найден, значит, его в массиве нет.
    

### Почему он так эффективен?

Главное преимущество бинарного поиска в том, что на каждом шаге он отбрасывает половину оставшихся данных. Из-за этого количество проверок растет очень медленно по сравнению с ростом размера массива. Например, в массиве из миллиона элементов он найдет нужный не более чем за 20 сравнений, в то время как обычный перебор (линейный поиск) в худшем случае потребовал бы миллион сравнений.

> [!NOTE] 
> Асимптотическая сложность: O(log n).
> Количество дополнительной памяти: O(1).

## 3. Реализация

```c
typedef struct IEcoLab1* IEcoLab1Ptr_t;

typedef struct IEcoLab1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab1Ptr_t me);

    /* IEcoLab1 */
	int16_t (ECOCALLMETHOD *MyFunction)(/* in */ IEcoLab1Ptr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);
	int16_t (ECOCALLMETHOD *Bsearchi)(/* in */ IEcoLab1Ptr_t me, /* in */ const int* arr, /* in */ const int n, /* in */ const int target, /* out */ int* index);
	int16_t (ECOCALLMETHOD *Bsearchl)(/* in */ IEcoLab1Ptr_t me, /* in */ const long long* arr, /* in */ const int n, /* in */ const long long target, /* out */ int* index);
	int16_t (ECOCALLMETHOD *Bsearchf)(/* in */ IEcoLab1Ptr_t me, /* in */ const float* arr, /* in */ const int n, /* in */ const float target, /* out */ int* index);
	int16_t (ECOCALLMETHOD *Bsearchd)(/* in */ IEcoLab1Ptr_t me, /* in */ const double* arr, /* in */ const int n, /* in */ const double target, /* out */ int* index);
	int16_t (ECOCALLMETHOD *Bsearchld)(/* in */ IEcoLab1Ptr_t me, /* in */ const long double* arr, /* in */ const int n, /* in */ const long double target, /* out */ int* index);

} IEcoLab1VTbl, *IEcoLab1VTblPtr;

interface IEcoLab1 {
    struct IEcoLab1VTbl *pVTbl;
} IEcoLab1;
```

## 4. Тесты

### Реализация

Чтобы проверить эффективность написанных методов, были написаны функции, генерирующие массивы от 1000 до 10000000 элементов каждого представленного типа данных. При этом каждый элемент массива равен его индексу.

**Пример генерации целочисленного массива:**
```c
int* GenerateIntArray(IEcoMemoryAllocator1* pIMem, int size) {
    size_t i;
    int* arr = (int*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));

    for (i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}
```

Далее с помощью многочисленных запусков вычисляется среднее время отработки метода. Для замеров использовался QueryPerformanceCounter из windows.h, так как он позволяет вычислить наиболее точное время в наносекундах.

**Пример тестирования бинарного поиска для типа int:**
```c
void TestBsearchInt(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    int* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;

    printf("Binary search INT tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateIntArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            pIEcoLab1->pVTbl->Bsearchi(pIEcoLab1, arr, size, -1, &index);
        }
        QueryPerformanceCounter(&end);

        assert(index == -1);
        elapsed_ticks = end.QuadPart - start.QuadPart;
        avg_cpu_time_ns = ((double)elapsed_ticks * 1000000000.0 / g_performanceFrequency.QuadPart) / LAUNCH_COUNT;
        printf("test %d elements: %.2f ns.\n", size, avg_cpu_time_ns);
        pIMem->pVTbl->Free(pIMem, arr);
    }

    printf("Binary search INT tests completed\n\n");
}
```

Стоит заметить, что в массиве все элементы неотрицательны, но в тестах в качестве target выступает -1. Это сделано для того, чтобы основной цикл в бинарном поиске отработал полностью и оценка производительности была более справедливой.

### Результаты

![Terminal](https://github.com/VladZF/Eco.Lab1/blob/master/Pictures/Terminal.png)

![Charts](https://github.com/VladZF/Eco.Lab1/blob/master/Pictures/Charts.png)

По результатам можно сделать вывод, что даже массивы с огромным количеством элементов отрабатывают менее чем за 100 наносекунд. При этом можно заметить, что хоть и немного, но методы, обрабатывающие массивы с нецелыми числами работают дольше. В целом алгоритм реализован удачно. 