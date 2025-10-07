/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

 /* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

/* Подключаем заголовочный файл для QueryPerformanceCounter */
#include <windows.h>

#define SIZES_COUNT 5
#define LAUNCH_COUNT 100000

int g_testSizes[SIZES_COUNT] = { 1000, 10000, 100000, 1000000, 10000000 };

/* Глобальная переменная для хранения частоты счетчика */
LARGE_INTEGER g_performanceFrequency;

int* GenerateIntArray(IEcoMemoryAllocator1* pIMem, int size) {
    size_t i;
    int* arr = (int*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));

    for (i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

long long* GenerateLongLongArray(IEcoMemoryAllocator1* pIMem, int size) {
    int i;
    long long* arr = (long long*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(long long));

    for (i = 0; i < size; i++) {
        arr[i] = (long long)i;
    }
    return arr;
}

float* GenerateFloatArray(IEcoMemoryAllocator1* pIMem, int size) {
    int i;
    float* arr = (float*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(float));

    for (i = 0; i < size; i++) {
        arr[i] = (float)i;
    }
    return arr;
}

double* GenerateDoubleArray(IEcoMemoryAllocator1* pIMem, int size) {
    int i;
    double* arr = (double*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(double));

    for (i = 0; i < size; i++) {
        arr[i] = (double)i;
    }
    return arr;
}

long double* GenerateLongDoubleArray(IEcoMemoryAllocator1* pIMem, int size) {
    int i;
    long double* arr = (long double*)pIMem->pVTbl->Alloc(pIMem, size * sizeof(long double));

    for (i = 0; i < size; i++) {
        arr[i] = (long double)i;
    }
    return arr;
}

void TestBsearchInt(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    int* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;
    int result;

    printf("Binary search INT tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateIntArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            result = pIEcoLab1->pVTbl->Bsearchi(pIEcoLab1, arr, size, -1, &index);
            if (result != ERR_ECO_SUCCESES) {
                printf("Binary search INT tests failed\n");
                pIMem->pVTbl->Free(pIMem, arr);
                return;
            }
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

void TestBsearchLongLong(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    long long* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;
    int result;

    printf("Binary search LONG LONG tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateLongLongArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            result = pIEcoLab1->pVTbl->Bsearchl(pIEcoLab1, arr, size, -1LL, &index);
            if (result != ERR_ECO_SUCCESES) {
                printf("Binary search LONG LONG tests failed\n");
                pIMem->pVTbl->Free(pIMem, arr);
                return;
            }
        }
        QueryPerformanceCounter(&end);

        assert(index == -1);
        elapsed_ticks = end.QuadPart - start.QuadPart;
        avg_cpu_time_ns = ((double)elapsed_ticks * 1000000000.0 / g_performanceFrequency.QuadPart) / LAUNCH_COUNT;
        printf("test %d elements: %.2f ns.\n", size, avg_cpu_time_ns);
        pIMem->pVTbl->Free(pIMem, arr);
    }

    printf("Binary search LONG LONG tests completed\n\n");
}

void TestBsearchFloat(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    float* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;
    int result;

    printf("Binary search FLOAT tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateFloatArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            result = pIEcoLab1->pVTbl->Bsearchf(pIEcoLab1, arr, size, -1.0f, &index);
            if (result != ERR_ECO_SUCCESES) {
                printf("Binary search FLOAT tests failed\n");
                pIMem->pVTbl->Free(pIMem, arr);
                return;
            }
        }
        QueryPerformanceCounter(&end);

        assert(index == -1);
        elapsed_ticks = end.QuadPart - start.QuadPart;
        avg_cpu_time_ns = ((double)elapsed_ticks * 1000000000.0 / g_performanceFrequency.QuadPart) / LAUNCH_COUNT;
        printf("test %d elements: %.2f ns.\n", size, avg_cpu_time_ns);
        pIMem->pVTbl->Free(pIMem, arr);
    }

    printf("Binary search FLOAT tests completed\n\n");
}

void TestBsearchDouble(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    double* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;
    int result;

    printf("Binary search DOUBLE tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateDoubleArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            result = pIEcoLab1->pVTbl->Bsearchd(pIEcoLab1, arr, size, -1.0, &index);
            if (result != ERR_ECO_SUCCESES) {
                printf("Binary search DOUBLE tests failed\n");
                pIMem->pVTbl->Free(pIMem, arr);
                return;
            }
        }
        QueryPerformanceCounter(&end);

        assert(index == -1);
        elapsed_ticks = end.QuadPart - start.QuadPart;
        avg_cpu_time_ns = ((double)elapsed_ticks * 1000000000.0 / g_performanceFrequency.QuadPart) / LAUNCH_COUNT;
        printf("test %d elements: %.2f ns.\n", size, avg_cpu_time_ns);
        pIMem->pVTbl->Free(pIMem, arr);
    }

    printf("Binary search DOUBLE tests completed\n\n");
}

void TestBsearchLongDouble(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    long double* arr;
    int size_i;
    int launch_i;
    int size;
    int index;
    LARGE_INTEGER start, end;
    long long elapsed_ticks;
    double avg_cpu_time_ns;
    int result;

    printf("Binary search LONG DOUBLE tests started\n");

    for (size_i = 0; size_i < SIZES_COUNT; size_i++) {
        size = g_testSizes[size_i];
        arr = GenerateLongDoubleArray(pIMem, size);

        QueryPerformanceCounter(&start);
        for (launch_i = 0; launch_i < LAUNCH_COUNT; launch_i++) {
            result = pIEcoLab1->pVTbl->Bsearchld(pIEcoLab1, arr, size, -1.0L, &index);
            if (result != ERR_ECO_SUCCESES) {
                printf("Binary search LONG DOUBLE tests failed\n");
                pIMem->pVTbl->Free(pIMem, arr);
                return;
            }
        }
        QueryPerformanceCounter(&end);

        assert(index == -1);
        elapsed_ticks = end.QuadPart - start.QuadPart;
        avg_cpu_time_ns = ((double)elapsed_ticks * 1000000000.0 / g_performanceFrequency.QuadPart) / LAUNCH_COUNT;
        printf("test %d elements: %.2f ns.\n", size, avg_cpu_time_ns);
        pIMem->pVTbl->Free(pIMem, arr);
    }

    printf("Binary search LONG DOUBLE tests completed\n\n");
}


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Получаем частоту счетчика производительности ОДИН РАЗ в начале */
    if (!QueryPerformanceFrequency(&g_performanceFrequency)) {
        printf("High-resolution performance counter not supported.\n");
        return -1;
    }

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void**)&pISys);
        if (result != 0 && pISys == 0) {
            /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void**)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**)&pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Тестирование функций */
    TestBsearchInt(pIEcoLab1, pIMem);
    TestBsearchLongLong(pIEcoLab1, pIMem);
    TestBsearchFloat(pIEcoLab1, pIMem);
    TestBsearchDouble(pIEcoLab1, pIMem);
    TestBsearchLongDouble(pIEcoLab1, pIMem);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}