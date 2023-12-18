#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Classe abstrata
class cadastravel {
public:
    string nome;
    int id;

    cadastravel(string _nome, int _id) : nome(_nome), id(_id){};

    // Metodos abstratos
    virtual void imprimir_caracteristicas() = 0;
    string getNome(){ return nome; };
    int getId(){ return id; };
    
    void setNome(string _nome){ nome = _nome; }; // o nome pode ser alterado para nome social ou por razoes de casamento
    
    // Destrutor:
    virtual ~cadastravel() {} 
};

// Classe livro que herda de cadastravel
class livro : public cadastravel {
public:
    int ano;
    string autor;

    livro(string _nome, int _id, int _ano, string _autor)
        : cadastravel(_nome, _id), ano(_ano), autor(_autor) {};

    void imprimir_caracteristicas() override {
        
        cout << "Titulo: " << nome << endl;
        cout << "Autor: " << autor << endl;
        cout << "Ano: " << ano << endl;
        cout << endl;
        
    }

    void atualizar_dados(string _nome, int _id, int _ano, string _autor) {
        cout << "Atualizando dados do livro..." << endl;
        nome = _nome;
        id = _id;
        ano = _ano;
        autor = _autor;
    }

};


class emprestimo {
public:
    string prazo;
    string data;
    livro* titulo;

    emprestimo(string _prazo, livro* _titulo, string _data)
        : prazo(_prazo), titulo(_titulo), data(_data) {}

    void imprimir_caracteristicas() {
        
        cout << "Emprestimo:" << endl;
        cout << "Titulo: " << titulo->nome << endl;
        cout << "Data: " << data << endl;
        cout << "Prazo: " << prazo << endl;
        cout << endl;
        
    }

    void atualizar_dados(string _prazo) {
        cout << "Atualizando informações do empréstimo..." << endl;
        prazo = _prazo;
    }

};

// classe usuario herda de cadastravel
class usuario : public cadastravel {
public:
    vector<emprestimo*> emprestimos;

    usuario(string _nome, int _id)
        : cadastravel(_nome, _id) {}

    void imprimir_caracteristicas() override {
       cout << "Nome: " << nome << endl;
       cout << "Id: " << id << endl;
    }

    void atualizar_dados(string _nome, int _id) {
        cout << "Atualizando informações do usuário..." << endl;
        nome = _nome;
        id = _id;
    }

    void realizar_emprestimo(emprestimo* e) {
        emprestimos.push_back(e);
    }
    
    void imprimir_emprestimos(){
        cout << "Emprestimos de " << nome << " :" << endl;
        for(auto &emprestimo : emprestimos){
            emprestimo->imprimir_caracteristicas();
            cout << endl;
        }
    }
    
    void devolver_emprestimo(string titulo) {
    for (auto it = emprestimos.begin(); it != emprestimos.end(); ++it) {
        if ((*it)->titulo->getNome() == titulo) {
            cout << "Emprestimo devolvido!" << endl;
            emprestimos.erase(it);
            return;
        }
    }

    cout << "Emprestimo não encontrado!" << endl;
    return;  
}
};


 // funcao polimorfica para excluir objetos cadastraveis
void deletar_cadastravel(cadastravel* objeto) {
    delete objeto;
}


template <typename T>
bool existe_id(vector<T*>& objetos, int _id) {
    for (auto &objeto : objetos)
        if (objeto->id == _id)
            return true;

    return false;
}

template <typename T>
T* buscar_objeto(vector<T*>& objetos, int id){
    
    if(existe_id(objetos, id)){
        for(auto&objeto: objetos)
            if(objeto->getId() == id)
                return objeto;
    }else{
        cout << "Nao foi encontrado cadastro relacionado a id informada!" << endl;
    }
    return nullptr;
}

void deletar_emprestimo(emprestimo* e, usuario* solicitante){
    delete e; // remove do vetor de execucao
}

int main() {
   
   
    int continua = -1;
    
    vector<usuario*> usuarios;
    vector<livro*> livros;
    
    // Create: criar novos cadastraveis
    // Read: mostrar informacoes de cadastraveis
    // Update: alterar informacoes de cadastraveis
    // Delete: remover polimorficamente cadastraveis do sistema, remover emprestimos
    
    // opcoes do menu:
    /*
    1 - Cadastrar usuario (C)
    2-  Cadastrar volume (C)
    3 - Consultar acervo (R)
    4 - Consultar usuario (R)
    5 - Atualizar dados cadastrais (U)
    6 - Alterar informacao de obra (U)
    7 - Realizar Empresitmo (U)
    8 - Devolver Emprestimo (U/D)
    9 - Remover usuario/volume do cadastro (D)
    0 - Sair
    */
    
    while(continua){
        
        cout << "Selecione a opcao desejada:" << endl;
        cout << "1) Cadastrar usuario\n2) Cadastrar volume\n3) Consultar acervo\n4) Consultar usuario\n5) Atualizar dados cadastrais\n6) Alterar Informacoes da obra\n7) Realizar emprestimo\n8) Devolver empresitmo\n9) Remover usuario/livro do sistema\n0) sair\n\n>";
        cin >> continua;
    
    if(continua == 1){
        
        string nome;
        int id;
        
        cout << "Insira as informacoes do usuario: " << endl;
        cout << "\nNome: " << endl;
        cin >> nome;
        cout << "\nId: " << endl;
        cin >> id;
        
        
        if(!existe_id(usuarios, id)){
        
        usuario* novo = new usuario(nome, id);
        usuarios.push_back(novo);
        cout << "\nusuario cadastrado com sucesso!" << endl;
            
        }else{
            
        cout << "\nja existe um usuario com esta id!" << endl;
                
            }
            cout << endl;
    }

        
        if(continua == 2){
            
            string titulo;
            int ano;
            string autor;
            int id;
            
             cout << "Insira as informacoes do livro: " << endl;
             cout << "\nTitulo: " << endl;
             getline(cin >> ws, titulo);
             cout << "\nId: " << endl;
             cin >> id;
             cout << "\nAno: " << endl;
             cin >> ano;
             cout << "\nAutor: " << endl;
             getline(cin >> ws, autor);
            
            if(!existe_id(livros, id)){
                
                livro* novo = new livro(titulo, id, ano, autor);
                livros.push_back(novo);
                cout << "Volume cadastrado com sucesso!\n" << endl;
                
            }else{
                cout << "Ja existe um livro com essa id no sistema!\n" << endl;
            }
            cout << endl;
        }
        
        if(continua == 3){
            
            int id;
            
            cout << "Insira a id do livro procurado: " << endl;
            cin >> id;
            
            if(existe_id(livros, id))
                for(auto &livro: livros)
                    if(livro->getId() == id)
                        livro->imprimir_caracteristicas();
            cout << endl;
        }

        if(continua == 4){
            
            int id;
            
            cout << "Insira a id do usuario procurado: " << endl;
            cin >> id;
            
            if(existe_id(usuarios, id)){
                for(auto &usuario: usuarios)
                    if(usuario->getId() == id){
                        usuario->imprimir_caracteristicas();
                        usuario->imprimir_emprestimos();
                    }
            }else{
                cout << "Usuario nao encontrado!" << endl;
            }
            cout << endl;
        }

        if(continua == 5){
            
            int id;
            cout << "Insira a id do usuario procurado: ";
            cin >> id;
        
            usuario* busca = buscar_objeto(usuarios, id);
            
            if(busca != nullptr){
                string nome;
                
                cout << "Insira a alteracao a ser feita no nome do usuario: ";
                cin >> nome;
                
                busca->setNome(nome);
            }
            cout << endl;
        }
        
        if(continua == 6){
            
            int id;
            cout << "Insira a id do livro procurado: ";
            cin >> id;
        
            livro* busca = buscar_objeto(livros, id);
            
            if(busca != nullptr){
                string titulo;
                string autor;
                int ano;
                
                cout << "Iniciando recadastramento. Preencha os campos com as informacoes desejadas:" << endl;
                cout << "Insira o titulo: " << endl;
                getline(cin >> ws, titulo);
                cout << "Insira o ano: " << endl;
                cin >> ano;
                cout << "Insira o nome do autor: " << endl;
                getline(cin >> ws, autor);
                
                busca->atualizar_dados(titulo, id, ano, autor);
            }
            cout << endl;
        }
                if(continua == 7){
            
            int id_livro;
            int id_usuario;
            
            string data;
            string prazo;
            
            cout << "Indique a id do volume que deseja emprestar";
            cin >> id_livro;
            cout << "Indique a id do usuario que fara o emprestimo";
            cin >> id_usuario;
            
            livro* emprestado = buscar_objeto(livros, id_livro);
            usuario* requerente = buscar_objeto(usuarios, id_usuario);
            
            if(emprestado != nullptr){
                cout << "Informe o prazo" << endl;
                getline(cin >> ws, prazo);
            
                cout << "Informe a data atual (DD/MM/AAAA)" << endl;
                getline(cin >> ws, data);
            
                emprestimo* novo_emprestimo = new emprestimo(prazo, emprestado, data);
                requerente->realizar_emprestimo(novo_emprestimo);
            }else{
                cout << "Nao foi encontrado livro no sistema com a id informada";
            }
            cout << endl;
        }
        
        if(continua == 8){
            
            int id;
            
            cout << "Insira a id do usuario: " << endl;
            cin >> id;
            
            if(existe_id(usuarios, id)){
                for(auto &usuario : usuarios)
                    if(usuario->id == id){
                        
                        string titulo;
                        
                        cout << "Insira o nome do titulo a ser removido dos emprestimos" << endl;
                        getline(cin >> ws, titulo);
                        
                        usuario->devolver_emprestimo(titulo);
                        
                    }
            }
            cout << endl;
        }
                if(continua == 9){
            
            int selecao;
            int id;
            
            cout << "Selecione o tipo de dado a ser removido:\n1) livro\n2) usuario\n3) sair" << endl;
            cin >> selecao;
            
            if(selecao != 3){
                
                cout << "Informe a id:" << endl;
                cin >> id;
                
                if(selecao == 1){
                    livro* busca = buscar_objeto(livros, id);
                    if(busca != nullptr)
                        deletar_cadastravel(busca);
                }else{
                    usuario* busca = buscar_objeto(usuarios, id);
                    if(busca != nullptr)
                        deletar_cadastravel(busca);
                }
        }
        cout << endl;
        }
        
        cout << endl;
    }
   
    usuarios.clear();
    livros.clear();
    
    return 0;
}
