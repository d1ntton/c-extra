#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Ativo {
    string ticket;
    int quantidade;
    double preco_medio;
};

vector<Ativo> ativos;


int buscaBinaria(const vector<Ativo>& v, const string& ticket, int baixo, int alto) {
    if (baixo > alto) {
        return -1;
    }

    int meio = baixo + (alto - baixo) / 2;

    if (v[meio].ticket == ticket) {
        return meio;
    } else if (v[meio].ticket > ticket) {
        return buscaBinaria(v, ticket, baixo, meio - 1);
    } else {
        return buscaBinaria(v, ticket, meio + 1, alto);
    }
}


void adicionarAtivo(const Ativo& novoAtivo) {
    int index = buscaBinaria(ativos, novoAtivo.ticket, 0, ativos.size() - 1);

    if (index != -1) {

        Ativo& ativoExistente = ativos[index];
        double custoTotal = ativoExistente.preco_medio * ativoExistente.quantidade;
        custoTotal += novoAtivo.preco_medio * novoAtivo.quantidade;
        ativoExistente.quantidade += novoAtivo.quantidade;
        ativoExistente.preco_medio = custoTotal / ativoExistente.quantidade;
    } else {

        ativos.push_back(novoAtivo);
        sort(ativos.begin(), ativos.end(), [](const Ativo& a, const Ativo& b) {
            return a.ticket < b.ticket;
        });
    }
}


void registrarCompra() {
    Ativo novoAtivo;

    cout << "Digite o ticket (ex: ITSA4): ";
    cin >> novoAtivo.ticket;

    cout << "Digite a quantidade comprada: ";
    cin >> novoAtivo.quantidade;

    cout << "Digite o valor do ativo no momento da compra: ";
    cin >> novoAtivo.preco_medio;

    adicionarAtivo(novoAtivo);
}


void registrarVenda() {
    string ticket;
    int quantidade;
    double precoVenda;

    cout << "Digite o ticket (ex: ITSA4): ";
    cin >> ticket;

    int index = buscaBinaria(ativos, ticket, 0, ativos.size() - 1);

    if (index == -1) {
        cout << "Ativo não encontrado." << endl;
        return;
    }

    cout << "Digite a quantidade vendida: ";
    cin >> quantidade;

    Ativo& ativo = ativos[index];

    if (quantidade > ativo.quantidade) {
        cout << "Quantidade maior do que o disponível." << endl;
        return;
    }

    ativo.quantidade -= quantidade;

    if (ativo.quantidade == 0) {

        ativos.erase(ativos.begin() + index);
    }
}

void verSaldo() {
    string ticket;

    cout << "Digite o ticket (ex: ITSA4): ";
    cin >> ticket;

    int index = buscaBinaria(ativos, ticket, 0, ativos.size() - 1);

    if (index == -1) {
        cout << "Ativo nao encontrado." << endl;
    } else {
        const Ativo& ativo = ativos[index];
        cout << "Saldo do ativo " << ativo.ticket << ": " << ativo.quantidade
             << " ações, preço medio: " << fixed << setprecision(2) << ativo.preco_medio << endl;
    }
}

void listarPatrimonio() {
    cout << "Patrimonio total:" << endl;

    for (const auto& ativo : ativos) {
        cout << "Ticket: " << ativo.ticket << ", Quantidade: " << ativo.quantidade
             << ", Preço Medio: " << fixed << setprecision(2) << ativo.preco_medio << endl;
    }
}


int main() {
    int escolha;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Registrar compra" << endl;
        cout << "2. Registrar venda" << endl;
        cout << "3. Ver o saldo de um ativo (Busca por Ticket)" << endl;
        cout << "4. Listar Patrimonio" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                registrarCompra();
                break;
            case 2:
                registrarVenda();
                break;
            case 3:
                verSaldo();
                break;
            case 4:
                listarPatrimonio();
                break;
            case 5:
                cout << "Saindo do sistema." << endl;
                break;
            default:
                cout << "Opção invalida. Tente novamente." << endl;
                break;
        }

    } while (escolha != 5);

    return 0;
}
