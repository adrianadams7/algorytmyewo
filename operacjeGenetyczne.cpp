
#include <cstdlib>
#include <ctime>
#include <iostream>
#define CH_SIZE 10
#define NUM_RANGE 100
#define OS_COUNT 4
//tworzenie klasy osobnik(wypelnienie chromosomow osobnikami)
class Osobnik {
public:
	int chromosom[CH_SIZE];
	Osobnik() {
		for (int i = 0; i < CH_SIZE; i++)
		{
			chromosom[i] = rand() % (NUM_RANGE + 1);
		}
	}

	friend std::ostream& operator<< (std::ostream &out, const Osobnik &o);

};
std::ostream& operator<< (std::ostream &out, const Osobnik &o) {
	out << "|";
	for (int i = 0; i < CH_SIZE; i++)
	{
		out << o.chromosom[i] << "|";
	}
	return out;
}
//klasa odpowiadajaca za operacje gentyczne, fitness, mutacje ,krzyzowanie
class OperacjeGenetyczne {
private:
	Osobnik osobnicy[OS_COUNT];
public:
	OperacjeGenetyczne() {
		for (int i = 0; i < OS_COUNT; i++)
		{
			osobnicy[i] = Osobnik();
		}
	}
	int fitness(Osobnik o) {
		int parzyste = 0;
		int nieparzyste = 0;
		for (int i = 0; i < CH_SIZE; i++)
		{
			if (o.chromosom[i] % 2)
				nieparzyste += o.chromosom[i];
			else
				parzyste += o.chromosom[i];
		}
		return parzyste - nieparzyste;
	}
	Osobnik mutacja(Osobnik o, int ile) {
		std::cout << "MUTACJA: " << ile << std::endl;
		std::cout << "PRZED:" << o << std::endl;
		for (int i = 0; i < ile || i < CH_SIZE; i++)
		{
			o.chromosom[i] = 100 - o.chromosom[i];
		}
		std::cout << "PO:   " << o << std::endl;
		return o;
	}
	void krzyzowanie(Osobnik &o1, Osobnik &o2, int punktPodzialu) {
		std::cout << "KRZYZOWANIE: " << punktPodzialu << std::endl;
		std::cout << "PRZED:" << o1 << "       " << o2 << std::endl;
		for (int i = punktPodzialu; i < CH_SIZE; i++)
		{
			int tmp = o1.chromosom[i];
			o1.chromosom[i] = o2.chromosom[i];
			o2.chromosom[i] = tmp;
		}
		std::cout << "PO:   " << o1 << "       " << o2 << std::endl;
	}
//wyswietlanie chromosomow przed, oraz po operacjach
	void etap()
	{
		std::cout << "OSOBNICY PRZED: " << std::endl;
		for (int i = 0; i < OS_COUNT; i++)
		{
			std::cout << i << ". " << osobnicy[i] << "  ~fitness: " << fitness(osobnicy[i]) << std::endl;
		}
		//2 mutacje losowych osobników + 2 krzy¿owania losowych osobników
		int os1 = rand() % OS_COUNT;
		int os2 = rand() % OS_COUNT;
		while (os2 == os1)
			os2 = rand() % OS_COUNT;
		std::cout << "OSOBNICY: " << os1 << " i " << os2 << " ZMUTOWANI" << std::endl;
		osobnicy[os1] = mutacja(osobnicy[os1], rand() % CH_SIZE);
		osobnicy[os2] = mutacja(osobnicy[os2], rand() % CH_SIZE);

		int os3 = rand() % OS_COUNT;
		int os4 = rand() % OS_COUNT;
		while (os4 == os3)
			os4 = rand() % OS_COUNT;

		int os5 = rand() % OS_COUNT;
		int os6 = rand() % OS_COUNT;
		while (os6 == os5)
			os6 = rand() % OS_COUNT;

		std::cout << "OSOBNICY KRZYZOWANI PARAMI: " << os3 << " i " << os4 << " | " << os5 << " i " << os6 << std::endl;
		krzyzowanie(osobnicy[os3], osobnicy[os4], rand() % CH_SIZE);
		krzyzowanie(osobnicy[os5], osobnicy[os6], rand() % CH_SIZE);
		
		std::cout << "OSOBNICY PO: " << std::endl;
		for (int i = 0; i < OS_COUNT; i++)
		{
			std::cout << i << ". " << osobnicy[i] << "  ~fitness: " << fitness(osobnicy[i]) << std::endl;
		}
	}
};


int main()
{
	std::srand(std::time(NULL));
	OperacjeGenetyczne op = OperacjeGenetyczne();
	for (int i = 0; i < 4; i++)
	{
		std::cout << "ETAP " << i + 1 << ":" << std::endl;
		op.etap();
	}
    return 0;
}

