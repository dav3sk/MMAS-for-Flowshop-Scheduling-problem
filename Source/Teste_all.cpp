#include <windows.h>
#include <vector>
#include <string>

#define EXECUCOES 30

using namespace std;

string ACO = "ACO.exe";
string GERACOES="15000";
vector<string> instancias = {"ta001.txt", "ta010.txt", "ta020.txt", "ta030.txt", "ta040.txt", "ta050.txt", "ta060.txt", "ta070.txt", "ta080.txt", "ta090.txt", "ta100.txt", "ta110.txt"};

void Executa(string N_FORMIGAS, string TAXA_EVAPORACAO, string PROB_GLOBAL) {
	for (int i=0 ; i < 12 ; ++i) {
		for (int e=0 ; e < EXECUCOES ; ++e) {
			string EXEC = ACO + " " + N_FORMIGAS + " " + TAXA_EVAPORACAO + " " + GERACOES + " " + PROB_GLOBAL + " " + instancias.at(i);
			system(EXEC.data());
			system("echo .");
		}
	}
}

int main () {

	Executa("5", "0.75", "0.1");
	Executa("5", "0.75", "0.5");
	Executa("5", "0.75", "0.9");

	Executa("5", "0.80", "0.1");
	Executa("5", "0.90", "0.1");
	Executa("5", "0.99", "0.1");

	Executa("1", "0.75", "0.1");
	Executa("1", "0.75", "0.5");
	Executa("1", "0.75", "0.9");

	Executa("1", "0.80", "0.1");
	Executa("1", "0.90", "0.1");
	Executa("1", "0.99", "0.1");

	return 0;
}
