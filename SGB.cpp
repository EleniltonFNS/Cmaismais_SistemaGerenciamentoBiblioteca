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
    system("clear");
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
        case 1:
        system("clear");
        cout << endl << " -=-=-=-=-=-=- Cadastro de Livros -=-=-=-=-=-=- " << endl;
        cout << endl << " - Deseja cadastrar um livro (S)im ou (N)ão:" << endl;
        cout << " -> ";
        cin >> opc;
        cin.get();

        while (opc == 's' || opc == 'S') {
            system("clear");
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

            sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+");

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
            system("clear");
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

                while (!feof(sistemaBiblioteca)) {
                    fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
                    if (cod == livro.codigo && !livro.excluido) {
                    encontrado = true;
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " -=- Código: " << livro.codigo << endl;
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
                    }
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
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
                cout << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
                break;
            }
            break;
        case 3: // Exclusão de cadastro
            system("clear");
            if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb+")) != NULL) {
                cout << endl << " -=-=-=-=-=-=- Exclusão de cadastro -=-=-=-=-=-=- " << endl;
                cout << endl << " - Deseja excluir o cadastro de um livro (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();

                while (opc == 's' || opc == 'S') {
                    system("clear");
                    cout << endl << " -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- " << endl;
                    cout << endl << " - Informe o código do livro a ser excluido: -=-=-=-=-=-=-=-=- " << endl;
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
                            cout << " Status: Dispónivel para empréstimo" << endl;
                        
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
                        cout << endl << " -=-=-=- Livro não encontrado ou já excluído! -=-=-=- " << endl;

                    } else if (livro.statusDisponibilidade == false){
                        cout << endl << " -=-=-=- Não é possível realizar a exclusão desse cadastro, pois o livro está emprestado! -=-=-=-" << endl;
                    }

                    cin.ignore();
                    cin.get();

                    system("clear");
                    cout << endl << " -=-=-=-=-=-=- Exclusão de cadastro -=-=-=-=-=-=- " << endl;
                    cout << endl << " - Deseja excluir o cadastro de um outro livro (S)im ou (N)ão:" << endl;
                    cout << " -> ";
                    cin >> opc;
                    cin.get();
                }
                fclose(sistemaBiblioteca);
            } else {
                cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
                break;
            }
            break;
        case 4: // Empréstimos de livros
            system("clear");
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
                                cout << endl << " -=-=-=- Livro emprestado com sucesso! -=-=-=- ";
                            } else {
                                cout << endl << " -=-=-=- Erro ao realizar emprestimo do livro! -=-=-=- ";
                            }
                            break;
                        }
                        posicao++;
                    }
                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou já excluído! -=-=-=- " << endl;
                    } else if (livro.statusDisponibilidade == false){
                        cout << endl << " -=-=-=- Livro já está emprestado! -=-=-=-" << endl;
                    }
                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
                    break;
                }
                system("clear");
                cout << endl << " -=-=-=-=-=-=- Confirmado o emprestimo -=-=-=-=-=-=- " << endl;
                cout << endl << " - Deseja realizar o emprestimo de outro livro (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();
            }
            break;
        case 5: // Devolução do livro
            system("clear");
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

                    while (!feof(sistemaBiblioteca)) {
                        fread(&livro, sizeof(struct Livros), 1, sistemaBiblioteca);
                        if (cod == livro.codigo && !livro.excluido && livro.statusDisponibilidade == false) {
                            encontrado = true;
                            cout << endl << " Código: " << livro.codigo << endl;
                            cout << " Título: " << livro.titulo << endl;
                            cout << " Autor(es): " << livro.autores << endl;
                            cout << " Editora: " << livro.editora << endl;
                            cout << " Área de atuação: " << livro.area << endl;
                            cout << " Número de páginas: " << livro.numPaginas << endl;
                            cout << " Status: Emprestado para " << livro.emprestimoLivro.nomeUsuario << endl;

                            fseek(sistemaBiblioteca, sizeof(struct Livros) * posicao, SEEK_SET);
                            livro.statusDisponibilidade = true; // Livro disponível após a devolução
                                
                            strcpy(livro.emprestimoLivro.nomeUsuario, "");
                            strcpy(livro.emprestimoLivro.dataEmprestimo, "");
                            strcpy(livro.emprestimoLivro.dataDevolucao, "");

                            if (fwrite(&livro, sizeof(struct Livros), 1, sistemaBiblioteca) == 1) {
                                cout << endl << " -=-=-=- Devolução registrada com sucesso! -=-=-=- ";
                            } else {
                                cout << endl << " -=-=-=- Erro ao registrar a devolução do livro! -=-=-=- ";
                            }
                            break;
                        }
                        posicao++;
                    }

                    if (!encontrado) {
                        cout << endl << " -=-=-=- Livro não encontrado ou já excluído! -=-=-=- " << endl;
                    }
                    fclose(sistemaBiblioteca);
                } else {
                    cout << endl << " -=-=-=- Erro ao abrir o banco de dados! -=-=-=- ";
                }
                system("clear");
                cout << endl << " -=-=-=-=-=-=- Devolução Confirmada -=-=-=-=-=-=- " << endl;
                cout << endl << " - Deseja registrar a devolução de outro livro (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();
            }
            break;
        case 6: // Consulta de Livro
            system("clear");
            if ((sistemaBiblioteca = fopen("dadosBiblioteca.txt", "rb")) != NULL) {
                cout << endl << " -=-=-=-=-=-=- Consulta de Livro -=-=-=-=-=-=- " << endl;
                cout << endl << " - Deseja consultar um livro (S)im ou (N)ão:" << endl;
                cout << " -> ";
                cin >> opc;
                cin.get();
    
                while (opc == 's' || opc == 'S') {
                system("clear");
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
    
                system("clear");
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
            system("clear");
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
            system("clear");
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