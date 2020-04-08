**João Víctor Bolsson Marques**

Diretiva utilizada:
``` c
int i;
#pragma omp parallel for schedule(static, nTimes) shared(array) private(i) num_threads(nThreads)
for (i = 0; i < nThreads * nTimes; i++)
    array->addChar('A' + omp_get_thread_num(), i)
```

Cada thread executa `nTimes`, o número de trheads que serão executadas é definido por `nThreads`. O `for` irá repetir `nThreads * nTimes` vezes. Traduzindo para os parâmetros utilizados nos testes, sendo `nTimes = 20` e `nThreads = 3`, o loop irá executar 60 vezes.

Saída:
```
Each thread should add its char to the array n times (n=20)
Correct results should total exactly nThreads*nTimes chars
Expecting correct results
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20
```

Usando schedule com `static`, cada thread receberá uma parcela do loop para executar. O tamanho da parcela é definido pelo `chunk = nTimes` nesse caso. Ou seja, cada thread executará 20 vezes, independemente das outras. Como cada thread tem um "id" que representará o `char` inserido, terão 20 caracteres iguais para cada uma. Dessa forma, garantimos que todas as threads executarão o mesmo número de vezes nesse caso.
