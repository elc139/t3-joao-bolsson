**João Víctor Bolsson Marques**

Cada thread executa `nTimes`, o número de trheads que serão executadas é definido por `nThreads`. O `for` irá repetir `nThreads * nTimes` vezes. Traduzindo para os parâmetros utilizados nos testes, sendo `nTimes = 20` e `nThreads = 3`, o loop irá executar 60 vezes.

### **Saída:**
```
Case: static with chunk
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 


Case: static without chunk
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 


Case: dynamic with chunk
CCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 


Case: dynamic without chunk
BCACBACBACBACBACBACBACBACABCCABCABCABCABCABCABCBACABCABCCABC
A=19 B=19 C=22 


Case: guided with chunk
BBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAA
A=20 B=20 C=20 


Case: guided without chunk
BBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCAAAAAAAAAAAAAAACCCCAAACCCA
A=19 B=20 C=21 


Case: runtime
BCACABCABCABCABCABCABCACBACBCABCABCABCBACBACCBACBACBACBACBAC
A=19 B=19 C=22 


Case: auto
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20
```

---
### Case 1: static with chunk
---
Usando schedule com `static`, cada thread receberá uma parcela do loop para executar. O tamanho da parcela é definido pelo `chunk = nTimes` nesse caso. Ou seja, cada thread executará 20 vezes, independemente das outras. Como cada thread tem um "id" que representará o `char` inserido, terão 20 caracteres iguais para cada uma. Dessa forma, garantimos que todas as threads executarão o mesmo número de vezes nesse caso.

---
### Case 2: static without chunk
---
Cada threads executará um determinado número de vezes independentemete das outras. Como não definimos um `chunk` ele será calculado visando que a tarefa seja dividida igualmente entre as threads. Nesse caso, como temos 60 iterações e 3 threads, o número de execuções para cada uma será 20, igual ao caso anterior.

---
### Case 3: dynamic with chunk
---
Usando `dynamic` se uma threads terminar a sua parcela de execução e outra parcela estiver disponível para execução (sem estar sendo executada por outra thread), então a thread que terminou a execução da sua parcela, vai executar outro chunk disponível. No caso de teste isso não acontece, pois temos apenas 3 parcelas e 3 threads, logo, nunca vai ter nenhum chunk sobrando.

---
### Case 4: dynamic without chunk
---
Mesmo caso do exemplo anterior, porém, sem a especificação do chunk caberá ao compilador calcular o tamanho das parcelas a serem executadas por cada thread.

---
### Case 5: guided with chunk
---
Semelhante ao caso 3. Cada threads receberá uma parcela de tamanho = `chunk`. Se uma thread terminar e ainda restar iterações que não foram designadas para nenhuma thread, então a thread irá executar um novo chunk ainda não executado, porém, esse chunk será menor que o chunk original, visto que será calculado com base no número de iterações restantes a serem feitas dividido pelo número de threads. Ou seja, se sobrarem 6 iterações existirem 3 threads, a thread que terminou irá executar um chunk = 2, e sobrará 4 iterações ainda. As outras threads farão o mesmo.

---
### Case 6: guided without chunk
---
Mesma situação do caso anterior, única diferença é que como o chunk não foi especificado o compilador calculará o chunk com base no número de iterações a serem feitas e o número de threads, visando sempre definir números iguas (ou próximos) de iterações para cada uma das threads.

---
### Case 7: runtime
---
Conforme material disponível em: http://jakascorner.com/blog/2016/06/omp-for-scheduling.html no caso do schedule ser definido como runtime o OpenMP usará o schedule definido pela variável de controle interna `run-sched-var`, que pode ser definida alterando a variável de ambiente `OMP_SCHEDULE` ou por chamada da função `omp_set_schedule`. Por padrão, `run-sched-var=static` e tem o mesmo efeito do caso 2.

---
### Case 8: auto
---
Aqui o schedule será definido pelo compilador e/ou pelo sistema. Pode ser qualquer tipo de schedule definido anteriormente.