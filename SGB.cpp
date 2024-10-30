#include <iostream>
#include <cstdio> // Struct.
#include <limits> // cin.ignore(numeric_limits<streamsize>::max(), '\n').
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

if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "ab+")) == NULL) {
    sistemaBiblioteca = fopen("dadosBiblioteca.txt", "wb");
}

do {
    system("cls");
    cout << endl << " -=-=- Sistema de Administração de Biblioteca -=-=- " << endl << endl;
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
        case 1: // Cadastro de livros
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
                
                // Verificar se o código já existe
                bool codigoExiste;
                do {
                    codigoExiste = false;
                    cout << endl << " Código: ";
                    cin >> livro.codigo;
                    cin.get();
                    
                    FILE *verificacao = fopen("dadosBiblioteca.txt", "rb");
                    struct Livros livroTemp;
                    while (fread(&livroTemp, sizeof(struct Livros), 1, verificacao) == 1) {
                        if (livroTemp.codigo == livro.codigo && !livroTemp.excluido) {
                            cout << " Código já existe! Por favor, escolha outro código." << endl;
                            codigoExiste = true;
                            break;
                        }
                    }
                    fclose(verificacao);
                } while (codigoExiste);

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
                
                do {
                    cout << " Número de páginas: ";
                    cin >> livro.numPaginas;
                    if (livro.numPaginas <= 0) {
                        cout << " Número de páginas inválido! Digite um número maior que 0." << endl;
                    }
                } while (livro.numPaginas <= 0);

                livro.statusDisponibilidade = true;
                livro.excluido = false;

                sistemaBiblioteca = fopen("dadosBiblioteca.txt", "ab+");

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
                    cout << endl << " -=- Informe o código do livro a ser alterado -=- " << endl;
                    cout << " Código: ";
                    cin >> cod;
                    cin.get();

                    int posicao = 0;
                    bool encontrado = false;
                    
                    rewind(sistemaBiblioteca); // Volta ao início do arquivo
                    
                    while (fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                        if (cod == livro.codigo && !livro.excluido) {
                            encontrado = true;
                            cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                            cout << " Código atual: " << livro.codigo << endl;
                            cout << " Título atual: " << livro.titulo << endl;
                            cout << " Autor(es) atual: " << livro.autores << endl;
                            cout << " Editora atual: " << livro.editora << endl;
                            cout << " Área atual: " << livro.area << endl;
                            cout << " Número de páginas atual: " << livro.numPaginas << endl;
                            
                            cout << endl << " Digite os novos dados:" << endl;
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
                            cin.get();

                            fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                            if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                cout << endl << " -=-=-=- Livro alterado com sucesso! -=-=-=- " << endl;
                            } else {
                                cout << endl << " -=-=-=- Erro ao alterar dados do livro! -=-=-=- " << endl;
                            }
                            break;
                        }
                        posicao++;
                    }

                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou excluído! -=-=-=- " << endl;
                    }

                    cout << endl << " - Deseja alterar outro livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();
                }
                fclose(sistemaBiblioteca);
            } else {
                cout << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- " << endl;
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
                    cout << endl << " - Informe o código do livro a ser excluido: -=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " Código: ";
                    cin >> cod;
                    cin.get();

                    int posicao = 0;
                    bool encontrado = false;
                    rewind(sistemaBiblioteca);

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
                                
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                                char opcExcluir;
                                cout << "- Confirmar exclusão do cadastro de livro (S)im ou (N)ão:";
                                cout << " -> ";
                                cin >> opcExcluir;
                                cin.get();

                                if (opcExcluir == 's' || opcExcluir == 'S') {
                                    livro.excluido = true;
                                    fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                    if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                        cout << endl << " -=-=-=- Livro excluído com sucesso! -=-=-=- " << endl;
                                    } else {
                                        cout << endl << " -=-=-=- Erro ao excluir o livro! -=-=-=- " << endl;
                                    }
                                } else {
                                    cout << endl << " -=-=-=- Exclusão cancelada! -=-=-=- " << endl;
                                }
                            } else {
                                cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                                cout << endl << " -=-=-=- Não é possível excluir um livro que está emprestado! -=-=-=- " << endl;
                            }
                            break;
                        }
                        posicao++;
                    }

                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou já excluído! -=-=-=- " << endl;
                    }

                    cout << endl << " - Deseja tentar excluir outro livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();
                }
                fclose(sistemaBiblioteca);
            } else {
                cout << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- " << endl;
            }
            break;

        case 4: // Empréstimos de livros
            system("cls");
            cout << endl << " -=-=-=-=-=-=- Realizar emprestimo de livros -=-=-=-=-=-=- " << endl;
            cout << endl << " - Deseja realizar o emprestimo de um livro (S)im ou (N)ão:" << endl;
            cout << " -> ";
            cin >> opc;
            cin.get();

            while (opc == 's' || opc == 'S') {
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " - Informe o código do livro a ser emprestado: -=-=-=-=-=- " << endl;
                    cout << endl << " Código: ";
                    cin >> cod;
                    cin.get();

                    int posicao = 0;
                    bool encontrado = false;
                    rewind(sistemaBiblioteca);

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
                                cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl << endl;

                                cout << " Nome do usuário: ";
                                cin.get(livro.emprestimoLivro.nomeUsuario, 255);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << " Data do empréstimo (DD/MM/AAAA): ";
                                cin.get(livro.emprestimoLivro.dataEmprestimo, 10);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << " Data prevista para devolução (DD/MM/AAAA): ";
                                cin.get(livro.emprestimoLivro.dataDevolucao, 10);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                livro.statusDisponibilidade = false;

                                fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                    cout << endl << " -=-=-=- Livro emprestado com sucesso! -=-=-=- " << endl;
                                } else {
                                    cout << endl << " -=-=-=- Erro ao realizar emprestimo do livro! -=-=-=- " << endl;
                                }
                            } else {
                                cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;
                                cout << endl << " -=-=-=- Este livro já está emprestado! -=-=-=- " << endl;
                            }
                            break;
                        }
                        posicao++;
                    }

                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou excluído! -=-=-=- " << endl;
                    }

                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- " << endl;
                    break;
                }

                cout << endl << " - Deseja realizar outro empréstimo (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();
            }
            break;

        case 5: // Devolução do livro
            system("cls");
            cout << endl << " -=-=-=-=-=-=- Registrar devolução de livros -=-=-=-=-=-=- " << endl;
            cout << endl << " - Deseja registrar a devolução de um livro (S)im ou (N)ão:" << endl;
            cout << " -> ";
            cin >> opc;
            cin.get();

            while (opc == 's' || opc == 'S') {
                if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " - Informe o código do livro a ser devolvido: -=-=-=-=-=- " << endl;
                    cout << endl << " Código: ";
                    cin >> cod;
                    cin.get();

                    int posicao = 0;
                    bool encontrado = false;
                    rewind(sistemaBiblioteca);

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

                            if (!livro.statusDisponibilidade) {
                                cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;

                                char opcDevolver;
                                cout << endl << "- Confirmar devolução do livro (S)im ou (N)ão:";
                                cout << " -> ";
                                cin >> opcDevolver;
                                cin.get();

                                if (opcDevolver == 's' || opcDevolver == 'S') {
                                    livro.statusDisponibilidade = true;
                                    strcpy(livro.emprestimoLivro.nomeUsuario, "");
                                    strcpy(livro.emprestimoLivro.dataEmprestimo, "");
                                    strcpy(livro.emprestimoLivro.dataDevolucao, "");

                                    fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                                    if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                        cout << endl << " -=-=-=- Devolução registrada com sucesso! -=-=-=- " << endl;
                                    } else {
                                        cout << endl << " -=-=-=- Erro ao registrar a devolução! -=-=-=- " << endl;
                                    }
                                } else {
                                    cout << endl << " -=-=-=- Devolução cancelada! -=-=-=- " << endl;
                                }
                            } else {
                                cout << " Status: Disponível para empréstimo" << endl;
                                cout << endl << " -=-=-=- Este livro não está emprestado! -=-=-=- " << endl;
                            }
                            break;
                        }
                        posicao++;
                    }

                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou excluído! -=-=-=- " << endl;
                    }

                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- " << endl;
                }
                system("cls");
                cout << endl << " -=-=-=-=-=-=- Devolução Confirmada -=-=-=-=-=-=- " << endl;
                cout << endl << " - Deseja registrar a devolução de outro livro (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();
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
    
                cin.ignore();
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
                cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
            }
            break;
    
        case 7: // Livros Disponíveis
            system("cls");
            if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb")) != NULL) {
                cout << endl << " -=-=-=-=-=-=- Livros Disponíveis -=-=-=-=-=-=- " << endl;
    
                bool encontrouLivros = false;
    
                while (fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                if (livro.statusDisponibilidade && !livro.excluido && livro.statusDisponibilidade == true) {
                    encontrouLivros = true;
                    cout << endl << " Código: " << livro.codigo << endl;
                    cout << " Título: " << livro.titulo << endl;
                    cout << " Autor(es): " << livro.autores << endl;
                    cout << " Editora: " << livro.editora << endl;
                    cout << " Área de atuação: " << livro.area << endl;
                    cout << " Número de páginas: " << livro.numPaginas << endl;
                    cout << " ---------------------------------------- " << endl;
                }
                }
    
                if (!encontrouLivros) {
                cout << " -=-=-=- Não há livros disponíveis no momento! -=-=-=- " << endl;
                }
    
                fclose(sistemaBiblioteca);
            } else {
                cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
            }
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
                    if (livro.statusDisponibilidade) {
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
                cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
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