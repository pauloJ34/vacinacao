#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string>

using namespace std;

string vacinas[4]={"CORONAVAC","PFIZER","ASTRAZENECA", "JANSEN"};

typedef struct reg{
	string nome;
	string cpf;
	string data;
	string vacina;
	string dose;
	struct reg * anterio;
	struct reg * proximo;
}Celula;


Celula * criaNovaCelula(string dados[]){
	Celula * nova_celula = (Celula *) malloc(sizeof(Celula));

  nova_celula->nome = dados[0];
	nova_celula->cpf = dados[1];
	nova_celula->data = dados[2];
	nova_celula->vacina = dados[3];
	nova_celula->dose = dados[4];
	nova_celula->anterio = NULL;
	nova_celula->proximo = NULL;

	return nova_celula;
}


string menu(){
	string opcao;
	cout << "\n";
	cout << "Opções:\n";
	cout << "[1] Adicionar Vacinação\n";
	cout << "[2] Imprimir tudo\n";
	cout << "[3] Total de vacinados de hoje\n";
	cout << "[4] Vacinas por tipo\n";
	cout << "[5] Vacinas por dose\n";
	cout << "[0] SAIR\n";
	cout << "Escolha uma opção: ";
	cin >> opcao;
	//cin.sync();
	return opcao;
}


Celula * add(Celula * c){
	string dados[5];

	cout << "\n";
	cout << "Nome: ";
	cin >> dados[0];
	cout << "CPF: ";
	cin >> dados[1];
	cout << "Data: ";
	cin >> dados[2];
	if(dados[2]=="hoje"){
		struct tm * data_hora;
		time_t seg;
		time(&seg);
		data_hora = localtime(&seg);
		dados[2] = to_string(data_hora->tm_mday)+"/"+to_string(data_hora->tm_mon+1)+"/"+to_string(data_hora->tm_year+1900);
		
	}
	for(int i=0;i<4 ; i++){
		cout << "["<< vacinas[i][0] << "]" << vacinas[i] << " ";
	}
	cout << "\n";
	cout << "Vacina: ";
	cin >> dados[3];
	dados[3]= toupper(dados[3][0]);
	cout << "Dose: ";
	cin >> dados[4];
		
	Celula * novo = criaNovaCelula(dados);
	novo->proximo=c;
	if(c !=NULL){
		c->anterio=novo;
	}
	return novo;
}


void listar(Celula * c){
	Celula * listar;
	if(c==NULL){
		cout << "Não existe Dados ainda!";
	}else{
		for(listar= c; listar != NULL ; listar=listar->proximo){
			cout << "\n" << "Nome: " << listar->nome<<"\n";
			cout << "CPF: " <<listar->cpf<<"\n";
			cout << "Data: " << listar->data<<"\n";
			cout << "Vacina: " << listar->vacina<< "\n";
			cout << "Dose: " << listar->dose << "\n";
		}
	}
}

string listar_hoje(Celula * c){
	int numerar = 0;
	Celula * listar;
	if(c==NULL){
		return "Não existe Dados ainda!";
	}else{
		struct tm * data_hora;
		time_t seg;
		time(&seg);
		data_hora = localtime(&seg);
		string data = to_string(data_hora->tm_mday)+"/"+to_string(data_hora->tm_mon+1)+"/"+to_string(data_hora->tm_year+1900);
		for(listar= c; listar != NULL ; listar=listar->proximo){
			if(listar->data == data){
				numerar++;
			}
		}
		return "Foram vacinados " + to_string(numerar) + "hoje.";
	}
}

string listar_tipo(Celula * c){
	int numerar[4] = {0,0,0,0};
	/*string tipo;
	cout << "tipo da vacina: ";
	cin >> tipo;
	cout << tipo;*/
	Celula * listar;
	if(c==NULL){
		return "Não existe Dados ainda!";
	}else{
		//tipo = toupper(tipo[0]);
		/*if(tipo.length()==1){
			tipo = toupper(tipo[0]);
		}
		else{
			string add="";
			char tmp;
			for(int i=0; i<tipo.length() ; i++){
				tmp =toupper(tipo[i]);
				add= add+tmp;
			}
			tipo=add;
		}*/
		string txt;
		
		for(listar= c; listar != NULL ; listar=listar->proximo){
			switch(listar->vacina[0]){
				case 'C':
					numerar[0] = numerar[0]+1;
					break;
				case 'P':
					numerar[1] = numerar[1]+1;
					break;
				case 'A':
					numerar[2] = numerar[2]+1;
					break;
				case 'J':
					numerar[3] = numerar[3]+1;
					break;
				default:
					break;
				
			}
		}
		for(int i =0 ; i<4 ;i++){
			txt = txt + "Com "+vacinas[i]+" foram vacinados: " + to_string(numerar[i])+"\n";
		}
		return txt;
	}
	
}


int main() {
	Celula *celulas = NULL;
	int escolha;
	struct tm * data_hora;
	time_t seg;
	time(&seg);
	data_hora= localtime(&seg);
	do{

		string opcao=menu();
		
		/*try{*/ escolha=stoi(opcao); //} catch(invalid_argument& e){ escolha= -1;}
		
		switch(escolha){
			case 0:
				cout << "\nbye\n\n";
				break;
			case 1://adcionar dado
				celulas = add(celulas);
				break;				
			case 2://listar dados
				listar(celulas);
				break;
			case 3://listar vacinado hoje
				cout << "\n";
				cout << listar_hoje(celulas);
				cout << "\n";
				break;
			case 4://listar por tipo
				cout << "\n";
				cout << listar_tipo(celulas);
				cout << "\n";
				break;
			case 5://listar por vacina
				listar(celulas);
				break;
			default:
				cout << "\nValor incorreto\n";
				break;
		}		
		//Celula *listar =celulas;
	}while(escolha != 0);
}