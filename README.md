# Bar Chart Race
## Linguagem de Programação 1 - DIM0120 - 2020.6

This project aims to build a [Bar Chart](https://en.wikipedia.org/wiki/Bar_chart) Race, executed in text mode via terminal.

In the development of this program was used architecture game loop. basically formed by three main functions: process, update and render. To more info about game loop [click here](http://gameprogrammingpatterns.com/game-loop.html).

This program need a file with format CSV file, where your data is separate by commas.

To test program add more files

#### To compile the program use Make file

| Command | Description |
| ------- | --------- |
| `make all` | Compile all files. |
| `make objFolder` | Create bin folder. |
| `make bcr` | Create executable file(need *.o files, compilable in `make all`). |
| `make bin/main.o` | `Build the main` object. |
| `make clear` | Remove all *.o and bin file. |

###### Available in [GitHub](https://github.com/speeds0n/bcr-project) and [GitLab](https://projetos.imd.ufrn.br/edsoncassiano0/bar-chart-race).
###### Author Edson Cassiano. October, 2020
