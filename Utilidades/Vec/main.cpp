#include <iostream>
#include "Vec3_SIMD.h"
//#include "TArray2.h"
//#include "Vec2.h"


//#include <chrono>
//#include <filesystem>
//#include <thread>

#include <emmintrin.h>
#include <immintrin.h>

int main()
{
    //NewPush
    /* double a[3] __attribute__ ((aligned (16)));
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;

    double b[3] __attribute__ ((aligned (16)));
    b[0] = 6.0;
    b[1] = 7.0;
    b[2] = 8.0;

    __m256d* ptra = (__m256d*)a; 
    __m256d* ptrb = (__m256d*)b; 
    _mm256_store_pd(a, _mm256_add_pd(*ptra, *ptrb));

    std::cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';*/
    
    #ifdef __SSE__
    std::cout << "SSE" << std::endl;
    #endif
    std::cout << "hello\n";
    Vec3<float> a(1.0f);
    Vec3<float> b(2.0f);

    Vec3<double> c(4.0f);
    Vec3<double> d(6.0f);



    a += b;
    c += d;
    c -= d;

    std::cout << a << '|' << c << std::endl;
 
    return 0;
}
/* void ola()
{
    std::cout << "ola" << std::endl;
}*/


    /* Vec2<double> teste2(2.35f,5.64f);
    std::cout << teste2 << std::endl;
    Vec3<double> teste(4.3,6.5,8.5);
    std::cout << teste << std::endl;
    return 0;
   uint8_t o = 176;
    std::cout << "aaaa: " << static_cast<unsigned>(o) << std::endl;


    TArray2<Vec3<uint8_t>> array(2, 2);
    std::cout << "tamanho de um float: " << sizeof(uint8_t) << std::endl;
    std::cout << "bytes: " << array.bytes() << std::endl;*/

    /* for(unsigned i = 0; i < 2; ++i)
    {
        for(unsigned j = 0; j < 2; ++j)
        {
            array(i,j) = Vec3<uint8_t>(i+j+(i*j));
            std::cout << array(i,j) << " | ";
        }
       
    }

    for(auto const & i : array)
    {
        std::cout << i << ' ';
    }
    return 0;

    array.resizeTo(3,3);
    for(unsigned i = 0; i < 4; i++)
    {
        for(unsigned j = 0; j < 4; j++)
        {
            //array(i,j) = (float)i+j;
            std::cout << array(i,j) << ' ';
        }
       
    }*/
    /* std::cout << "olha mundo\n"; 

    std::filesystem::path aki = std::filesystem::current_path();
    std::cout << aki << std::endl;

    std::thread t1(ola);
    t1.join();*/

    /* constexpr unsigned TAMANHO_ARRAY = 4096;

    Vec3<float> arrayDeVecs[TAMANHO_ARRAY];

    for(unsigned i = 0; i < TAMANHO_ARRAY; ++i)
    {
        arrayDeVecs[i] = Vec3<float>((float)(i+1));
    }

    auto start = std::chrono::steady_clock::now();

    for(unsigned i = 0; i < TAMANHO_ARRAY; ++i)
    {
        for(unsigned j = 0; j < TAMANHO_ARRAY; ++j)
        {
            arrayDeVecs[i] += arrayDeVecs[i].Length();
            arrayDeVecs[i] /= arrayDeVecs[i].Length();
            arrayDeVecs[i] -= arrayDeVecs[i].Length();
            arrayDeVecs[i] *= arrayDeVecs[i].Length();
        }
    }

    for(unsigned i = 0; i < 4; ++i)
    {
        std::cout << arrayDeVecs[i] << std::endl;
    }

    auto end = std::chrono::steady_clock::now();
 
    // Store the time difference between start and end
   auto diff = end - start;

   std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    

} */