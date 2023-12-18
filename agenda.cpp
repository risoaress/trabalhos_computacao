#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Contato {
public:

    Contato() = default;

    Contato(string _nome, int _telefone, string _endereco, string _relacao) :
        nome(_nome), telefone(_telefone), endereco(_endereco), relacao(_relacao) {}

    string getNome() const { return nome; }
    long long getTelefone() const { return telefone; }
    string getEndereco() const { return endereco; }
    string getRelacao() const { return relacao; }

    void setNome(const string& n) { nome = n; }
    void setTelefone(long long t) { telefone = t; }
    void setEndereco(const string& e) { endereco = e; }
    void setRelacao(const string& r) { relacao = r; }

    string getInfo() const {
        return nome + " " + to_string(telefone) + " " + endereco + " " + relacao + "\n";
    }

private:
    string nome;
    long long telefone;
    string endereco;
    string relacao;
};

class Agenda {
public:
    Contato* busca_contato(const string& nome) {
        for (auto& c : contatos)
            if (c.getNome() == nome)
                return &c;
        return nullptr;
    }

    void remover_contato(const string& nome) {
        
         for (auto it = contatos.begin(); it != contatos.end(); it++) {
        if (it->getNome() == nome) {
            contatos.erase(it);
            cout << "Contato removido com sucesso!" << endl;
            return;
        }
    }

    cout << "Contato não encontrado!" << endl;
    }

    void editar_contato(const string& n, long long t, const string& e, const string& r) {
        Contato* c = busca_contato(n);
        if (c) {
            c->setNome(n);
            c->setTelefone(t);
            c->setEndereco(e);
            c->setRelacao(r);
        }
    }

    void inserir_contato(const Contato& c) {
        Contato* busca = busca_contato(c.getNome());

        if (busca == nullptr)
            contatos.push_back(c);
        else
            editar_contato(c.getNome(), c.getTelefone(), c.getEndereco(), c.getRelacao());
    }

    void mostrar_agenda() const {
        for (const auto& contato : contatos)
            cout << contato.getInfo();
    }


void carregar_contatos(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        contatos.clear(); // Limpar contatos existentes antes de carregar

        string nome;
        int telefone;
        string endereco;
        string relacao;

        while (arquivo >> nome >> telefone >> endereco >> relacao) {
            contatos.push_back(Contato(nome, telefone, endereco, relacao));
        }

        arquivo.close();
        cout << "Contatos carregados com sucesso." << endl;
    } else {
        cerr << "Erro ao abrir o arquivo para carregar contatos." << endl;
    }
    }

    void salvar_contatos(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        for (auto &c : contatos) {
            arquivo << c.getNome() << " " << c.getTelefone() << " " << c.getEndereco() << " " << c.getRelacao() << endl;
        }

        arquivo.close();
        cout << "Contatos salvos com sucesso." << endl;
    } else {
        cerr << "Erro ao abrir o arquivo para salvar contatos." << endl;
    }
    }

    void mostrar_contato(const string& n){
    Contato* busca = busca_contato(n);
    
    if(busca){
        cout << busca->getInfo() << endl;
        }
    }

private:
    vector<Contato> contatos;
};

class Principal{
public:

    Agenda agenda;
    
    void mostrar_contatos(){
        cout << endl << "Agenda:" << endl; 
            agenda.mostrar_agenda();
            cout << endl;
    }
    
    void realizar_consulta(){
        string nome;
            
            cout << "Digite o nome do contato desejado: ";
            cin >> nome;
            
            cout << endl << "Informacoes do contato: " << endl;
            agenda.mostrar_contato(nome);
            cout << endl;
    };
    
    void iniciar_cadastro(){
            string nome;
            long long tel;
            string end;
            string rel;
            
            cout << "Digite as informacoes do contato:\n" << endl; 
            cout << "Nome: ";
            getline(cin >> ws, nome);
            cout << "\nTelefone: ";
            cin >> tel;
            cin.ignore();
            cout << "\nEndereco: ";
            getline(cin >> ws, end);
            cout << "\nRelacao: ";
            getline(cin >> ws, rel);
            
            agenda.inserir_contato(Contato(nome, tel, end, rel));
            cout << endl;
    }
    
    void excluir_contato(){
        string nome;
            
            cout << "Digite o nome do contato desejado: ";
            cin >> nome;
            
            agenda.remover_contato(nome);
            cout << endl;
    }
    
    void salvar_arquivo(){
      
      string nome;
            
            cout << "Digite o nome do arquivo desejado: ";
            cin >> nome;
            
            agenda.salvar_contatos(nome);
            cout << endl;
        
    };
    
    void carregar_arquivo(){
        string nome;
            
            cout << "Digite o nome do arquivo desejado: ";
            cin >> nome;
            
            agenda.carregar_contatos(nome);
            cout << endl;
    };    
    
    
    
};

int main(){
    
    int continua;
    Principal principal;
    
    do{
        
        cout << "Selecione uma opcao:\n1) Ver agenda\n2) Ver contato\n3) Incluir novo contato\n4) Excluir contato\n5) Exportar agenda para arquivo binario\n6) Importar agenda de arquivo binario\n0) Sair\n> ";
        cin >> continua;
        
        if(continua == 1){
            principal.mostrar_contatos();
        }
        
        if(continua == 2){
            
            principal.realizar_consulta();
            
        }
        
        if(continua == 3){
            
            principal.iniciar_cadastro();
            
        }
        
        if(continua == 4){
            
            principal.excluir_contato();
            
        }
        
        if(continua == 5){
            
            principal.salvar_arquivo();
        }
        
        if(continua == 6){
            
            principal.carregar_arquivo();
        }
        
    }while(continua);
    
}
