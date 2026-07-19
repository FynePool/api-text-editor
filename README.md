# api-text-editor

[![CI](https://github.com/FynePool/api-text-editor/actions/workflows/ci.yml/badge.svg)](https://github.com/FynePool/api-text-editor/actions/workflows/ci.yml)

Progetto finale del corso **Algoritmi e Principi dell'Informatica** (Politecnico di Milano).

Un text editor a riga di comando scritto in C, con supporto a `undo`/`redo` illimitati, pensato e ottimizzato per gestire un numero molto elevato di comandi e righe di testo entro vincoli stretti di tempo e memoria.

## Comandi supportati

Il programma legge comandi da stdin fino al comando `q` (quit):

| Comando | Sintassi | Effetto | Complessità |
|---|---|---|---|
| Change | `c num1,num2` seguito da `num2-num1+1` righe di testo e da una riga contenente solo `.` | Sostituisce (o aggiunge) le righe da `num1` a `num2` | O(k) dove k = num2-num1, O(1) ammortizzato in caso di append sequenziale a fine testo |
| Delete | `d num1,num2` | Elimina le righe da `num1` a `num2` | O(num1 + k) per raggiungere e rimuovere l'intervallo |
| Print | `p num1,num2` | Stampa le righe da `num1` a `num2` (`.` per righe oltre la fine del testo) | O(num1 + k) |
| Undo | `u num` | Annulla gli ultimi `num` comandi che hanno modificato il testo | O(num · lunghezza testo) per la copia dello snapshot |
| Redo | `r num` | Ripristina i comandi precedentemente annullati | O(num · lunghezza testo) |
| Quit | `q` | Termina il programma | O(n) per la deallocazione finale |

Ogni comando che modifica il testo (`change`, `delete`) crea un nuovo stato nella cronologia; `undo`/`redo` si spostano lungo questa cronologia. Se viene eseguita una modifica dopo alcuni `undo`, la "storia futura" viene scartata.

## Struttura del repository

```
.
├── main.c              # implementazione finale dell'editor
├── Makefile            # target build / test / clean
├── iterations/          # versioni intermedie sviluppate durante il corso (vedi iterations/README.md)
├── tests/               # test pubblici (input/output) + test runner
├── docs/                # specifica ufficiale del progetto e screenshot di riferimento
└── .github/workflows/  # CI: build + test ad ogni push
```

- **[`main.c`](main.c)** — implementazione finale: lista concatenata di righe più lista concatenata di snapshot per la cronologia degli undo/redo, con alcune euristiche di ottimizzazione (accesso rapido a fine testo per append sequenziali, limite di memoria oltre il quale si smette di salvare cronologia).
- **[`iterations/`](iterations/)** — le versioni intermedie sviluppate durante il corso (da array fisso, a array di puntatori, a lista concatenata con snapshot), oltre a due varianti sperimentali (`bulkreads.c`, `rollingback.c`) focalizzate rispettivamente sull'ottimizzazione della lettura di grandi blocchi di testo e sulla velocità di `undo`/`redo`. Dettagli nel [README della cartella](iterations/README.md).
- **[`tests/`](tests/)** — i test pubblici forniti dal corso, organizzati per fase del progetto (rollercoaster, writeonly, rollingback, timeforachange, bulkreads, alteringhistory), più uno script (`run_tests.sh`) che confronta l'output dell'editor con quello atteso.
- **[`docs/`](docs/)** — testo ufficiale della specifica del progetto e screenshot di riferimento.

## Compilazione, esecuzione e test

```bash
make build   # compila main.c in ./editor
make test    # compila (se necessario) ed esegue tutti i test in tests/
make clean   # rimuove il binario compilato
```

L'editor legge i comandi da stdin, quindi può essere usato in modo interattivo oppure alimentato da un file di test:

```bash
./editor < tests/rollercoaster/Rollercoaster_1_input.txt
```

Una GitHub Action ([`.github/workflows/ci.yml`](.github/workflows/ci.yml)) esegue automaticamente build e test su ogni push/PR verso `main`.

## Note

Il progetto è stato sviluppato e valutato tramite un sistema di test automatico che imponeva vincoli precisi di tempo di esecuzione e memoria massima utilizzabile; le diverse versioni in [`iterations/`](iterations/) riflettono i tentativi successivi di rispettare tali vincoli su input via via più grandi.

## Licenza

Distribuito sotto licenza [MIT](LICENSE).
