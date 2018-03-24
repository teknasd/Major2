#include <iostream>
#include<vector>
#include<stdio.h>
#include<random>

using namespace std;

// Macros 
#define TIME 30
#define CHAN 16
#define USER 20
#define PROB 0.6
#define RWRD 1
#define GAMA 0.2

int rand_ac(int m)
{
	int var;
	std::uniform_int_distribution<int>  distr(0, 10000);
	std::random_device  rand_dev;
	std::mt19937        generator(rand_dev());
	var = distr(generator);

	return var%m;
}

double randno()
{
	double var;
	std::uniform_real_distribution<double>  distr(0,1);
	std::random_device  rand_dev;
	std::mt19937        generator(rand_dev());
	var = distr(generator);

	return var;
}

int main()
{
	int K, N, T, n, k, t, p, r,act,obs,col=0;
	float ran;
	K = CHAN;
	T = TIME;
	N = USER;
	vector <float> rewards(N, 0);
	vector <int> colisions(N, 0);
	vector <int> user_ac(N, 0);
	vector <int> actions(K,0);  
	vector <int> user_ob(N, 0);
	vector <vector<pair<int,int>>> history;
	pair<int, int> ac_ob;
	vector<pair<int, int>> row;

	for ( t = 0; t < T; t++)// time loop
	{
		for ( n = 0; n < N; n++)// user loop
		{
			act = rand_ac(K + 1);
			ran = randno();
			//cout << ran;
			if (ran <= PROB) {
				user_ac[n] = act;//user actions
				if (act) { actions[act - 1]++; }
			}
			//cout << user_ac[n];
		}//cout << endl<<"obs\n";

		for (int i = 0; i < K; i++)// set multiple trans as 0
		{
			if (actions[i] > 1) { actions[i] = 0; }
			//cout << actions[i];
		}//cout << endl;

		for (int i = 0;i < N; i++)// user loop
		{
			user_ob[i] = actions[user_ac[i]-1 > 0 ? user_ac[i] - 1 : 0];//user obs
			
											 
			//filling a history row
			ac_ob.first = user_ac[i];
			ac_ob.second = user_ob[i];
			row.push_back(ac_ob);


		}
		actions.resize(K,0);
		user_ac.resize(N, 0);
		user_ob.resize(N, 0);
		history.push_back(row);
		row.clear();
	}
	cout << "\n\nHISTORY\n\n";
	for (size_t i = 0; i < T; i++)
	{
		auto cum_r = 0.;

		for (size_t j = 0; j < N; j++)
		{
			cout << "[" << history[i][j].first << "," << history[i][j].second << "] ";
			//cum_r += pow(GAMA,i) *  history[i][j].second; 

		}cout << endl;
	}

	// rew
	cout << "\nREWARDS\n";
	for (size_t j = 0; j < N; j++)
	{
		auto cum_r = 0.;

		for (size_t i = 0; i < T; i++)
		{
			//cout << "[" << history[i][j].first << "," << history[i][j].second << "] ";
			cum_r += pow(GAMA, i) *  history[i][j].second;

		}//cout << endl;
		rewards[j] = cum_r;
		cout << cum_r << ", ";
	}

	system("pause");
	return 0;
}
