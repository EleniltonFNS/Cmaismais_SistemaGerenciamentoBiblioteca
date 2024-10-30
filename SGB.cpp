#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring> // Usado para fazer a atualização do cadastro dos livros.

using namespace std;

FILE *sistemaBiblioteca;

struct Emprestimos {
  char dataEmprestimo[10], dataDevolucao[10], nomeUsuario[255];
};

struct Livros {
  int codigo, numPaginas;
  char titulo[255], autores[255], editora[100], area[100];
  bool statusDisponibilidade, excluido;
  struct Emprestimos emprestimoLivro;
};

struct Livros livro;
char opc; 
int cod;
int opcaoMenu;

int main() {
  do {
    system("cls");
    cout << endl << " -=-=- Sistema de Administração de Biblioteca-=-=- " << endl << endl;
    cout << " | 1 - Cadastrar novo livro" << endl;
    cout << " | 2 - Alteração de cadastro" << endl;
    cout << " | 3 - Exclusão de cadastro" << endl;
    cout << " | 4 - Empréstimos de livros" << endl;
    cout << " | 5 - Devolução do livro" << endl;
    cout << " | 6 - Consulta de Livro" << endl;
    cout << " | 7 - Livros Disponíveis" << endl;
    cout << " | 8 - Listar livros cadastrados" << endl;
    cout << " | 9 - Sair" << endl;
    cout << endl << " -> ";
    cin >> opcaoMenu;
    cin.get();

    switch (opcaoMenu) {
      case 1:
        system("cls");
        cout << endl << " -=-=-=-=-=-=- Cadastro de Livros -=-=-=-=-=-=- " << endl;
        cout << endl << " - Deseja cadastrar um livro (S)im ou (N)ão:" << endl;
        cout << " -> ";
        cin >> opc;
        cin.get();

        while (opc == 's' || opc == 'S') {
          system("cls");
          cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
          cout << endl << " - Informe os dados do livro a serem cadastrados: -=- " << endl;
          cout << endl << " Código: ";
          cin >> livro.codigo;
          cin.get();
          cout << " Título: ";
          cin.get(livro.titulo, 255);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << " Autor(es): ";
          cin.get(livro.autores, 255);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << " Editora: ";
          cin.get(livro.editora, 100);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << " Área de atuação: ";
          cin.get(livro.area, 100);
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << " Número de páginas: ";
          cin >> livro.numPaginas;

          livro.statusDisponibilidade = true;
          livro.excluido = false;

          if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "ab+")) == NULL) {
            sistemaBiblioteca = fopen("dadosBiblioteca.txt", "wb");
          }

          if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
            cout << endl << endl << " -=-=-=- Livro cadastrado com sucesso! -=-=-=- " << endl;
          } else {
            cout << endl << endl << " -=-=-=- Erro ao cadastrar o livro! -=-=-=- " << endl;
          }
          fclose(sistemaBiblioteca);

          cout << endl << " - Deseja cadastrar um novo livro (S)im ou (N)ão:" << endl;
          cout << " -> ";
          cin >> opc;
          cin.get();
        }
        break;

      case 2:
        system("cls");
        if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
          cout << endl << " -=-=-=-=-=-=- Alteração de cadastro -=-=-=-=-=-=- " << endl;
          cout << endl << " - Deseja alterar o cadastro de um livro (S)im ou (N)ão:" << endl;
          cout << " -> ";
          cin >> opc;
          cin.get();

          while (opc == 's' || opc == 'S') {
            system("cls");
            cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
            cout << endl << " -=- Informe o código do livro a ser alterado -=- " << endl;
            cout << " Código: ";
            cin >> cod;
            cin.get();

            int posicao = 0;
            bool encontrado = false;

            while (!feof(sistemaBiblioteca)) {
              fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
              if (cod == livro.codigo && !livro.excluido) {
                encontrado = true;
                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                cout << endl << " Código: " << livro.codigo << endl;
                cout << " Título: " << livro.titulo << endl;
                cout << " Autor(es): " << livro.autores << endl;
                cout << " Editora: " << livro.editora << endl;
                cout << " Área de atuação: " << livro.area << endl;
                cout << " Número de páginas: " << livro.numPaginas << endl;
                if (livro.statusDisponibilidade) {
                    cout << " Status: Disponível para empréstimo" << endl;
                } else {
                    cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                }
                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                cout << " Título: ";
                cin.get(livro.titulo, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Autor(es): ";
                cin.get(livro.autores, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Editora: ";
                cin.get(livro.editora, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Área de atuação: ";
                cin.get(livro.area, 100);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << " Número de páginas: ";
                cin >> livro.numPaginas;

                fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                  cout << endl << " -=-=-=- Livro alterado com sucesso! -=-=-=- ";
                } else {
                  cout << endl << " -=-=-=- Erro ao alterar dados do livro! -=-=-=- ";
                }
                break;
              }
              posicao++;
            }

            if (!encontrado) {
              cout << endl << " -=-=-=- Livro não encontrado ou já excluído! -=-=-=- " << endl;
            }
            cout << endl << " - Deseja alterar outro livro (S)im ou (N)ão:" << endl;
            cout << " -> ";
            cin >> opc;
            cin.get();
          }
          fclose(sistemaBiblioteca);
        } else {
          cout << " Erro ao abrir o banco de dados! ";
        }
        break;
            case 3: // Exclusão de cadastro
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                    cout << endl << " -=-=-=-=-=-=- Exclusão de cadastro -=-=-=-=-=-=- " << endl;
                    cout << endl << " - Deseja excluir o cadastro de um livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();

                    while (opc == 's' || opc == 'S') {
                        system("cls");
                        cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                        cout << endl << " - Informe o código do livro a ser excluido: -=-=-=-=-=- " << endl;
                        cout << endl << " Código: ";
                        cin >> cod;
                        cin.get();

                        int posicao = 0;
                        bool encontrado = false;

                        while (!feof(sistemaBiblioteca)) {
                            fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
                            if (cod == livro.codigo && !livro.excluido) {
                                encontrado = true;
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                                cout << endl << " Código: " << livro.codigo << endl;
                                cout << " Título: " << livro.titulo << endl;
                                cout << " Autor(es): " << livro.autores << endl;
                                cout << " Editora: " << livro.editora << endl;
                                cout << " Área de atuação: " << livro.area << endl;
                                cout << " Número de páginas: " << livro.numPaginas << endl;
                                if (livro.statusDisponibilidade) {
                                    cout << " Status: Dispónivel para empréstimo" << endl;
                                } else {
                                    cout << endl << " -=-=-=- Não é possível realizar a exclusão desse cadastro, pois o livro está emprestado! -=-=-=-" << endl;
                                    break;
                                }
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                                char opcExcluir;
                                cout << "- Confirmar exclusão do cadastro de livro (S)im ou (N)ão:";
                                cout << " -> ";
                                cin >> opcExcluir;
                                cin.get();

                                if (opcExcluir == 's' || opcExcluir == 'S') {
                                    livro.excluido = true; // Marcar como excluído
                                    fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                    if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                        cout << endl << " -=-=-=- Livro excluído com sucesso! -=-=-=- ";
                                    } else {
                                        cout << endl << " -=-=-=- Erro ao alterar dados do livro! -=-=-=- ";
                                    }
                                } else {
                                    cout << endl << " -=-=-=- Exclusão cancelada! -=-=-=- ";
                                }
                                break;
                            }
                            posicao++;
                        }

                        if (!encontrado) {
                            cout << endl << " -=-=-=- Livro não encontrado ou excluído! -=-=-=- " << endl;
                        }

                        cin.ignore();
                        cin.get();

                        system("cls");
                        cout << endl << " -=-=-=-=-=-=- Exclusão de cadastro -=-=-=-=-=-=- " << endl;
                        cout << endl << " - Deseja excluir o cadastro de um outro livro (S)im ou (N)ão:" << endl;
                        cout << " -> ";
                        cin >> opc;
                        cin.get();
                    }
                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
                break;
            case 4: // Empréstimos de livros
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                    cout << endl << " -=-=-=-=-=-=- Registro de emprestimo -=-=-=-=-=-=- " << endl;
                    cout << endl << " - Deseja registrar o emprestimo de um livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();

                    while (opc == 's' || opc == 'S') {
                        system("cls");
                        cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                        cout << endl << " - Informe o código do livro a ser emprestado: -=-=-=-=-=- " << endl;
                        cout << endl << " Código: ";
                        cin >> cod;
                        cin.get();

                        int posicao = 0;
                        bool encontrado = false;

                        while (!feof(sistemaBiblioteca)) {
                            fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
                            if (cod == livro.codigo && !livro.excluido && livro.statusDisponibilidade == true) {
                                encontrado = true;
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                                cout << endl << " Código: " << livro.codigo << endl;
                                cout << " Título: " << livro.titulo << endl;
                                cout << " Autor(es): " << livro.autores << endl;
                                cout << " Editora: " << livro.editora << endl;
                                cout << " Área de atuação: " << livro.area << endl;
                                cout << " Número de páginas: " << livro.numPaginas << endl;
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;
                            
                                cout << " Nome: ";
                                cin.get(livro.emprestimoLivro.nomeUsuario, 255);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << " Data emprestimo: ";
                                cin.get(livro.emprestimoLivro.dataEmprestimo, 10);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << " Data devolução: ";
                                cin.get(livro.emprestimoLivro.dataDevolucao, 10);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                livro.statusDisponibilidade = false;

                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                                char opcEmpr;
                                cout << "- Confirmar emprestimo do livro (S)im ou (N)ão:";
                                cout << " -> ";
                                cin >> opcEmpr;
                                cin.get();

                                if (opcEmpr == 's' || opcEmpr == 'S') {
                                    fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                    if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                        cout << endl << " -=-=-=- Emprestimo de livro registrado com sucesso! -=-=-=- ";
                                    } else {
                                        cout << endl << " -=-=-=- Erro ao realizar emprestimo do livro! -=-=-=- ";
                                    }
                                } else {
                                    cout << endl << " -=-=-=- Emprestimo cancelado! -=-=-=- ";
                                }
                                break;
                            }
                            posicao++;
                        }

                        if (!encontrado) {
                            cout << endl << " -=-=-=- Livro não encontrado, ou está excluído, ou já foi emprestado! -=-=-=- " << endl;
                        }

                        cin.get();

                        system("cls");
                        cout << endl << " -=-=-=-=-=-=- Registro de emprestimo -=-=-=-=-=-=- " << endl;
                        cout << endl << " - Deseja registrar o emprestimo de um livro (S)im ou (N)ão:" << endl;
                        cout << " -> ";
                        cin >> opc;
                        cin.get();
                    }
                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
                break;

            case 5:
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                    cout << endl << " -=-=-=-=-=-=- Registro de devolução -=-=-=-=-=-=- " << endl;
                    cout << endl << " - Deseja registrar a devolução de um livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();

                    while (opc == 's' || opc == 'S') {
                        system("cls");
                        cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                        cout << endl << " - Informe o código do livro a ser devolvido: -=-=-=-=-=- " << endl;
                        cout << endl << " Código: ";
                        cin >> cod;
                        cin.get();

                        int posicao = 0;
                        bool encontrado = false;

                        while (!feof(sistemaBiblioteca)) {
                            fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
                            if (cod == livro.codigo && !livro.excluido && livro.statusDisponibilidade == false) {
                                encontrado = true;
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                                cout << endl << " Código: " << livro.codigo << endl;
                                cout << " Título: " << livro.titulo << endl;
                                cout << " Autor(es): " << livro.autores << endl;
                                cout << " Editora: " << livro.editora << endl;
                                cout << " Área de atuação: " << livro.area << endl;
                                cout << " Número de páginas: " << livro.numPaginas << endl;
                                cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;
                            
                                strcpy(livro.emprestimoLivro.nomeUsuario, ""); 
                                strcpy(livro.emprestimoLivro.dataEmprestimo, ""); 
                                strcpy(livro.emprestimoLivro.dataDevolucao, "");
                                livro.statusDisponibilidade = true;

                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                                char opcDevo;
                                cout << "- Confirmar devolução do livro (S)im ou (N)ão:";
                                cout << " -> ";
                                cin >> opcDevo;
                                cin.get();

                                if (opcDevo == 's' || opcDevo == 'S') {
                                    fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                    if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                        cout << endl << " -=-=-=- Devolução do livro registrado com sucesso! -=-=-=- ";
                                    } else {
                                        cout << endl << " -=-=-=- Erro ao realizar devolução do livro! -=-=-=- ";
                                    }
                                } else {
                                    cout << endl << " -=-=-=- Devolução cancelada! -=-=-=- ";
                                }
                                break;
                            }
                            posicao++;
                        }

                        if (!encontrado) {
                            cout << endl << " -=-=-=- Livro não encontrado, ou está excluído ou não está emprestado! -=-=-=- " << endl;
                        }

                        cin.get();

                        system("cls");
                        cout << endl << " -=-=-=-=-=-=- Registro de devolução -=-=-=-=-=-=- " << endl;
                        cout << endl << " - Deseja registrar a devolução de um outro livro (S)im ou (N)ão:" << endl;
                        cout << " -> ";
                        cin >> opc;
                        cin.get();
                    }
                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
                break;
            case 6: // Consulta de Livro
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb")) != NULL) {
                  cout << endl << " -=-=-=-=-=-=- Consulta de Livro -=-=-=-=-=-=- " << endl;
                  cout << endl << " - Deseja consultar um livro (S)im ou (N)ão:" << endl;
                  cout << " -> ";
                  cin >> opc;
                  cin.get();
        
                  while (opc == 's' || opc == 'S') {
                    system("cls");
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " - Informe o código do livro a ser consultado: -=-=-=-=-=- " << endl;
                    cout << endl << " Código: ";
                    cin >> cod;
                    cin.get();
        
                    bool encontrado = false;
        
                    while (fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                      if (cod == livro.codigo && !livro.excluido) {
                        encontrado = true;
                        cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                        cout << endl << " Código: " << livro.codigo << endl;
                        cout << " Título: " << livro.titulo << endl;
                        cout << " Autor(es): " << livro.autores << endl;
                        cout << " Editora: " << livro.editora << endl;
                        cout << " Área de atuação: " << livro.area << endl;
                        cout << " Número de páginas: " << livro.numPaginas << endl;
                        if (livro.statusDisponibilidade) {
                          cout << " Status: Disponível para empréstimo" << endl;
                        } else {
                          cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                        }
                        cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;
                        break;
                      }
                    }
        
                    if (!encontrado) {
                      cout << endl << " -=-=-=- Livro não encontrado excluído! -=-=-=- " << endl;
                    }
        
                    cin.get();
        
                    system("cls");
                    cout << endl << " -=-=-=-=-=-=- Consulta de Livro -=-=-=-=-=-=- " << endl;
                    cout << endl << " - Deseja consultar outro livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();
                  }
                  fclose(sistemaBiblioteca);
                } else {
                  cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
                break;
        
              case 7: // Livros Disponíveis
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb")) != NULL) {
                  cout << endl << " -=-=-=-=-=-=- Lista de Livros Disponíveis -=-=-=-=-=-=- " << endl;
                  int posicao = 0;
        
                  while (fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                    if (!livro.excluido && livro.statusDisponibilidade == true) {
                      cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                      cout << " Código: " << livro.codigo << endl;
                      cout << " Título: " << livro.titulo << endl;
                      cout << " Autor(es): " << livro.autores << endl;
                      cout << " Editora: " << livro.editora << endl;
                      cout << " Área de atuação: " << livro.area << endl;
                      cout << " Número de páginas: " << livro.numPaginas << endl;
                      cout << " Status: Disponível para empréstimo" << endl;
                      cout << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    }
                    posicao++;
                  }
        
                  if (posicao == 0) {
                    cout << endl << " -=-=-=- Nenhum livro disponível! -=-=-=- " << endl;
                  }
        
                  fclose(sistemaBiblioteca);
                } else {
                  cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
        
                cin.get();
                break;
        
            case 8: // Listar livros cadastrados
                system("cls");
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb")) != NULL) {
                  cout << endl << " -=-=-=-=-=-=- Lista de Livros Cadastrados -=-=-=-=-=-=- " << endl;
                  int posicao = 0;
        
                  while (fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                    if (!livro.excluido) {
                      cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                      cout << " Código: " << livro.codigo << endl;
                      cout << " Título: " << livro.titulo << endl;
                      cout << " Autor(es): " << livro.autores << endl;
                      cout << " Editora: " << livro.editora << endl;
                      cout << " Área de atuação: " << livro.area << endl;
                      cout << " Número de páginas: " << livro.numPaginas << endl;
                      if (livro.statusDisponibilidade == true) {
                        cout << " Status: Disponível para empréstimo" << endl;
                      } else {
                        cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                      }
                      cout << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    }
                    posicao++;
                  }
        
                  if (posicao == 0) {
                    cout << endl << " -=-=-=- Nenhum livro cadastrado! -=-=-=- " << endl;
                  }
        
                  fclose(sistemaBiblioteca);
                } else {
                  cout << endl << " Ocorreu um erro ao tentar abrir o banco de dados! ";
                }
        
                cin.get();
                break;
        
            case 9: // Sair
                cout << endl << " -=-=-=- Encerrando o sistema... -=-=-=- " << endl;
                break;
        
            default:
                cout << endl << " Opção inválida! Tente novamente. " << endl;
                break;
        }
  } while (opcaoMenu != 9);
  return 0;
}