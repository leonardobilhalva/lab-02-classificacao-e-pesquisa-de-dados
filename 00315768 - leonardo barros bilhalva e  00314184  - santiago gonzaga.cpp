//+------------------------------------------------------------------+
//|                                                   Laboratório 02 |
//|              Alunos: Leonardo Barros Bilhalva  e Santiago Gonzaga|
//|                     Disciplina: Classificação e Pesquisa de Dados|
//+------------------------------------------------------------------+

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

struct Statistics
{
    int swaps;
    int recursion;
    clock_t startTime;
    clock_t endTime;
};

Statistics stats = {swaps: 0, recursion: 0, startTime: 0, endTime: 0};

int averageOf3(vector<int> &vect, int low, int high) {
    int max, min, mid;

    max = high;
    min = low;
    mid = ((high - low) / 2) + low;                     //salva os indices do maior elemento, do menor e do meio
    
    if(vect[min] > vect[mid])
    {
    swap(vect[min], vect[mid]);                         //se o mínimo for maior que o maior, troca eles
    stats.swaps ++;
    }

    if(vect[min] > vect[max])
    {
    swap(vect[min], vect[max]);                         //se o mínimo for maior que o do meio, troca eles
    stats.swaps ++;
    }

    if(vect[mid] > vect[max])
    {
    swap(vect[mid], vect[max]);                         //se o do meio for maior que o maior, troca eles
    stats.swaps ++;
    }

    return mid;                                         //retorna o indice da mediana(elemento do meio)

}

int partitionLomutoAvg(vector<int> &vect, int low, int high)
{
    swap(vect[high], vect[averageOf3(vect, low, high)]);            //Aqui realizamos a função mediana e trocamos a mediana com o maior elemento
    stats.swaps ++;

    int pivot = vect[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high- 1; j++)                    //lomuto
    {
        if (vect[j] <= pivot)
        {
            i++;  
            swap(vect[i], vect[j]);
            stats.swaps++;
        }
    }
    swap(vect[i + 1], vect[high]);
    stats.swaps++;
    return (i + 1);
}

int partitionLomutoRandom(vector<int> &vect, int low, int high)
{
    int random = low + rand() % (high - low);           // seleciona um número aleatório, partindo do low, que esteja entre o low e o high
    swap(vect[random], vect[high]);                      // troca esse número com o high
    stats.swaps ++;

    int pivot = vect[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high- 1; j++)                //lomuto
    {
        if (vect[j] <= pivot)
        {
            i++;  
            swap(vect[i], vect[j]);
            stats.swaps++;
        }
    }
    swap(vect[i + 1], vect[high]);
    stats.swaps++;
    return (i + 1);
}

int partitionHoareAvg(vector<int> &vect, int low, int high)
{
   swap(vect[low], vect[averageOf3(vect, low, high)]);            //Aqui realizamos a função mediana e trocamos a mediana com o menor elemento
   stats.swaps++;

    int pivot = vect[low];
    
    int i = low - 1, j = high + 1;
 
    while (true) {                                          //hoare
        do {
            i++;
        } while (vect[i] < pivot);
 
        do {
            j--;
        } while (vect[j] > pivot);
 
        if (i >= j)
            return j;
 
        swap(vect[i], vect[j]);
        stats.swaps++;
    }
}

int partitionHoareRandom(vector<int> &vect, int low, int high)
{
    int random = low + rand() % (high - low);           // seleciona um número aleatório, partindo do low, que esteja entre o low e o high
    swap(vect[random], vect[low]);                      // troca esse número com o low
    stats.swaps ++;

    int pivot = vect[low];
    int i = low - 1, j = high + 1;
 
    while (true) {                                     //hoare
        do {
            i++;
        } while (vect[i] < pivot);
 
        do {
            j--;
        } while (vect[j] > pivot);
 
        if (i >= j)
            return j;
 
        swap(vect[i], vect[j]);
        stats.swaps++;
    }
}

void quickSortLomutoAvg(vector<int> &vect, int low, int high)
{
    if (low < high)
    {
        int pi = partitionLomutoAvg(vect, low, high);
 
        quickSortLomutoAvg(vect, low, pi - 1);
        quickSortLomutoAvg(vect, pi + 1, high);
    }
    stats.recursion++;
}

void quickSortLomutoRandom(vector<int> &vect, int low, int high)
{
    if (low < high)
    {
        int pi = partitionLomutoRandom(vect, low, high);
 
        quickSortLomutoRandom(vect, low, pi - 1);
        quickSortLomutoRandom(vect, pi + 1, high);
    }
    stats.recursion++;
}

void quickSortHoareAvg(vector<int> &vect, int low, int high)
{
    if (low < high)
    {
        int pi = partitionHoareAvg(vect, low, high);
 
        quickSortHoareAvg(vect, low, pi);
        quickSortHoareAvg(vect, pi + 1, high);
    }
    stats.recursion++;
}

void quickSortHoareRandom(vector<int> &vect, int low, int high)
{
    if (low < high)
    {
        int pi = partitionHoareRandom(vect, low, high);
 
        quickSortHoareRandom(vect, low, pi);
        quickSortHoareRandom(vect, pi + 1, high);
    }
    stats.recursion++;
}

void resetStats() {             // Funcao para resetar as estatisticas entre as funcoes
    stats.recursion = stats.swaps = stats.startTime = stats.endTime = 0;
}

int main(){
    cout << "Laboratorio 2 comecou" << endl;
	ifstream readingInput;            

	ofstream escrita_stats_mediana3_hoare; 
	ofstream escrita_stats_mediana3_lomuto;
	ofstream escrita_stats_aleatorio_hoare;
	ofstream escrita_stats_aleatorio_lomuto;

    escrita_stats_mediana3_hoare   << fixed << setprecision(6);
    escrita_stats_mediana3_lomuto  << fixed << setprecision(6);
    escrita_stats_aleatorio_hoare  << fixed << setprecision(6);
    escrita_stats_aleatorio_lomuto << fixed << setprecision(6);

    string line;
    string word;         
    vector<int> numbers; 
    vector<vector <int> > vetor_de_numeros;
    int quantidade_vetor_de_numeros = 0;
    int quantidade_numeros = 0;  

    readingInput.open("entrada-quicksort.txt");                            

    escrita_stats_mediana3_hoare.open("stats-mediana-hoare.txt");
    escrita_stats_mediana3_lomuto.open("stats-mediana-lomuto.txt");
    escrita_stats_aleatorio_hoare.open("stats-aleatorio-hoare.txt");
    escrita_stats_aleatorio_lomuto.open("stats-aleatorio-lomuto.txt");

    while(getline(readingInput, line))
    {        
      numbers.clear();            
      istringstream var(line);        
      getline(var, word, ' ');             
      quantidade_numeros = stoi(word);           
    
      while (quantidade_numeros > 0){            
      getline(var, word, ' ');                  
      numbers.push_back(stoi(word));             

      quantidade_numeros--;  
      }
      quantidade_vetor_de_numeros ++;
      vetor_de_numeros.push_back(numbers);
    }	

    //for (int i = 0; i < vetor_de_numeros.size(); i++) {                           //Deixei aqui essa funcao para conferir a leitura
    //    for (int j = 0; j < vetor_de_numeros[i].size(); j++)
    //        cout << vetor_de_numeros[i][j] << " ";
    //    cout << endl;
    //}

    vector<vector<int>> vetor_quicksort_mediana_3_lomuto = vetor_de_numeros;       //Duplicando os vetores que serao manipulados
    vector<vector<int>> vetor_quicksort_aleatorio_lomuto = vetor_de_numeros;
    vector<vector<int>> vetor_quicksort_mediana_3_hoare = vetor_de_numeros;    
    vector<vector<int>> vetor_quicksort_aleatorio_hoare = vetor_de_numeros; 

    for (unsigned int i = 0; i < vetor_de_numeros.size(); i++) {

        resetStats();
        escrita_stats_aleatorio_hoare << "TAMANHO ENTRADA " << vetor_quicksort_aleatorio_hoare[i].size() << endl;
        stats.startTime = clock();
        quickSortHoareRandom(vetor_quicksort_aleatorio_hoare[i], 0, vetor_quicksort_aleatorio_hoare[i].size()-1);
        stats.endTime = clock();  
        escrita_stats_aleatorio_hoare << "SWAPS #" << stats.swaps << endl;
        escrita_stats_aleatorio_hoare << "RECURSOES #" << stats.recursion << endl;
        escrita_stats_aleatorio_hoare << "TEMPO #" << (stats.endTime - stats.startTime) / (double) CLOCKS_PER_SEC << " EM SEGUNDOS" << endl;

        resetStats();
        escrita_stats_mediana3_hoare << "TAMANHO ENTRADA " << vetor_quicksort_mediana_3_hoare[i].size() << endl;
        stats.startTime = clock();
        quickSortHoareAvg(vetor_quicksort_mediana_3_hoare[i], 0, vetor_quicksort_mediana_3_hoare[i].size()-1);
        stats.endTime = clock();  
        escrita_stats_mediana3_hoare << "SWAPS #" << stats.swaps << endl;
        escrita_stats_mediana3_hoare << "RECURSOES #" << stats.recursion << endl;
        escrita_stats_mediana3_hoare << "TEMPO #" << (stats.endTime - stats.startTime) / (double) CLOCKS_PER_SEC << " EM SEGUNDOS" << endl;

        resetStats();
        escrita_stats_mediana3_lomuto << "TAMANHO ENTRADA " << vetor_quicksort_mediana_3_lomuto[i].size() << endl;
        stats.startTime = clock();
        quickSortLomutoAvg(vetor_quicksort_mediana_3_lomuto[i], 0, vetor_quicksort_mediana_3_lomuto[i].size()-1);
        stats.endTime = clock();  
        escrita_stats_mediana3_lomuto << "SWAPS #" << stats.swaps << endl;
        escrita_stats_mediana3_lomuto << "RECURSOES #" << stats.recursion << endl;
        escrita_stats_mediana3_lomuto << "TEMPO #" << (stats.endTime - stats.startTime) / (double) CLOCKS_PER_SEC << " EM SEGUNDOS" << endl;

        resetStats();
        escrita_stats_aleatorio_lomuto << "TAMANHO ENTRADA " << vetor_quicksort_aleatorio_lomuto[i].size() << endl;
        stats.startTime = clock();
        quickSortLomutoRandom(vetor_quicksort_aleatorio_lomuto[i], 0, vetor_quicksort_aleatorio_lomuto[i].size()-1);
        stats.endTime = clock();  
        escrita_stats_aleatorio_lomuto << "SWAPS #" << stats.swaps << endl;
        escrita_stats_aleatorio_lomuto << "RECURSOES #" << stats.recursion << endl;
        escrita_stats_aleatorio_lomuto << "TEMPO #" << (stats.endTime - stats.startTime) / (double) CLOCKS_PER_SEC << " EM SEGUNDOS" << endl;
    }

    readingInput.close();
    escrita_stats_aleatorio_hoare.close();
    escrita_stats_aleatorio_lomuto.close();
    escrita_stats_mediana3_hoare.close();
    escrita_stats_mediana3_lomuto.close();


    cout << "Laboratorio 2 terminou :)";
    return 0;
}
