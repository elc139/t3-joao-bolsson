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
### Case: static with chunk
---
Usando schedule com `static`, cada thread receberá uma parcela do loop para executar. O tamanho da parcela é definido pelo `chunk = nTimes` nesse caso. Ou seja, cada thread executará 20 vezes, independemente das outras. Como cada thread tem um "id" que representará o `char` inserido, terão 20 caracteres iguais para cada uma. Dessa forma, garantimos que todas as threads executarão o mesmo número de vezes nesse caso.
