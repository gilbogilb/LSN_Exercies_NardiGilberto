//main code for parallel computing with genetic algorithms
#include <iostream>
#include <fstream>
#include "mpi.h"
#include "proc_tsp.h" //travelling salesman with procedural functions
#include <string>

using namespace std;

int main(int argc, char* argv[]){

    MPI_Init(&argc,&argv);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat1, stat2;
    int itag=1; int itag2=2;
    int generations=1250, popsize=1000, ncities=32;
    int Nmigr=25;
    int* imesg = new int[ncities]; int* imesg2 = new int[ncities];
    Random general_rnd;
    general_rnd.Initialize(); //initialized with seed.in

    //differentating random seeds and output files
    ofstream out;
    for(int i=0; i<size; ++i){
        if(rank==i){
            string seed_name = "seed."+to_string(i);
            local_rnd.Initialize(1,"Primes",seed_name);
            string output_name = "parallel_data/best"+to_string(i)+".dat";
            out.open(output_name);
        }
    }
    ofstream testout("indextest.dat");

    //real GA simulation
    vector<vector<double>> cities = cities_in_square(ncities);
    vector<vector<int>> pop = generate_population(popsize,cities);

    for(int k=0; k<generations; ++k){
            int index = (int)general_rnd.Rannyu(1, size);
            testout << index << " ";

        //Migration code snippet
        if((k%Nmigr==0)&&k>0){
            vector<int> best = pop.at(0);
            for(int i=0;i<ncities;i++){imesg[i]=best.at(i); imesg2[i]=best.at(i);}

            //swapping 0 with index
            if(rank==index){
                MPI_Send(&imesg[0],ncities,MPI_INTEGER,0,itag,MPI_COMM_WORLD);
                MPI_Recv(&imesg2[0],ncities,MPI_INTEGER,0,itag2, MPI_COMM_WORLD,&stat2);
                cout<<"messaggio = "<<imesg2[0]<<endl;
                //out << imesg2[0] << endl;
                //update best vector
                for(int i=0; i<ncities; ++i) pop.at(0).at(i)=imesg2[i];
            }
            
            else if(rank==0){
                MPI_Send(&imesg2[0],ncities,MPI_INTEGER,index,itag2, MPI_COMM_WORLD);
                MPI_Recv(&imesg[0],ncities,MPI_INTEGER,index,itag, MPI_COMM_WORLD,&stat1);
                cout<<"messaggio = "<<imesg[0]<<endl;
                //out << imesg[0] << endl;
                //update best vector
                for(int i=0; i<ncities; ++i) pop.at(0).at(i)=imesg[i];
            }

            cout << "after the exchange: best vector in process " << rank << " is ";
            for(auto it=pop.at(0).begin(); it!=pop.at(0).end(); ++it)
                cout << *it << " ";
            cout << endl;

            //swapping the other two
            if(size==4){
                vector<int> i2;
                for(int i=1; i<size; ++i){
                    if(i!=index) i2.push_back(i);
                }

                if(rank==i2.at(0)){
                    MPI_Send(&imesg[0],ncities,MPI_INTEGER,i2.at(1),itag,MPI_COMM_WORLD);
                    MPI_Recv(&imesg2[0],ncities,MPI_INTEGER,i2.at(1),itag2, MPI_COMM_WORLD,&stat2);
                    cout<<"messaggio = "<<imesg2[0]<<endl;
                    //out << imesg2[0] << endl;
                    //update best vector
                    for(int i=0; i<ncities; ++i) pop.at(0).at(i)=imesg2[i];
                }
                
                else if(rank==i2.at(1)){
                    MPI_Send(&imesg2[0],ncities,MPI_INTEGER,i2.at(0),itag2, MPI_COMM_WORLD);
                    MPI_Recv(&imesg[0],ncities,MPI_INTEGER,i2.at(0),itag, MPI_COMM_WORLD,&stat1);
                    cout<<"messaggio = "<<imesg[0]<<endl;
                    //out << imesg[0] << endl;
                    //update best vector
                    for(int i=0; i<ncities; ++i) pop.at(0).at(i)=imesg[i];
                }

            }
            
        }

        make_generation(pop,cities,0.7,0.09,0.1,0.1);
        out << L2cost(pop.at(0),cities) << endl;
        cout << "k" << rank << "=" << k << endl;
    }

    out.close();
    testout.close();

    out.open("parallel_data/bestpath"+to_string(rank)+".dat");
    for(auto it=pop.at(0).begin(); it!=pop.at(0).end(); ++it)
        out << cities.at(*it).at(0) << " " << cities.at(*it).at(1) << endl;
    out.close();
    delete imesg2;
    delete imesg;
    MPI_Finalize();
return 0;
}