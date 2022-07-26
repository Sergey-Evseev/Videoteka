//Lesson 16: ������� ��������� ������������ �� ���������� ������:
// �������� ������; ��������; ����; ������� ������������; ���� �����.
// ����������� ��������� �����������:
// ����� �� ��������;
// ����� �� �����;
// ����� �� ���������;
// ����� ���������� ����� � �����;
// ����� ���� ������� � ����������.
// ��� ���������� ������ ����������� �������. ������� ��������� ����� ���������� � ������� ������� ��� ���������� ������.
// �������� ������ �������� �������� � ������ ���������� ������.


#include <iostream>
#include <string.h>
#include <string>
using namespace std;

enum genre { Drama, Comedy, Musical, Romance, Romantic�omedy, Detective, Action };
//������������ � ����������� � ���������� �� 0 �� 6

struct Movie { //��������� ������� ���������
	string name;
	string director;
	int genre;
	double rate;
	int price;	
};

string printGenre(int a) { //�� ���������� int ���������� ������ � ������� ������������ �������� �� �����
	string s = "";
	switch (a)
	{
	case Drama:
		s = "Drama";
		break;
	case Comedy:
		s = "Comedy";
		break;
	case Musical:
		s = "Musical";
		break;
	case Romance:
		s = "Romance";
		break;
	case Romantic�omedy:
		s = "Romantic Comedy";
		break;
	case Detective:
		s = "Detective";
		break;
	case Action:
		s = "Action";
		break;
	default:
		break;
	}
	return s; //���������� ������ � ������
}
void printMenuGenre() { //����� ������ - � ����� � printGenre ���������� �������� �� 0 �� 6 � ��������� �������. ������
	for (int i = 0; i < 7; i++) {
		cout << i << " - " << printGenre(i) << endl;
	}
}

void findGenre(Movie* movies, int size, int genre) {
	for (size_t i = 0; i < size; i++)
	{
		if (movies[i].genre == genre) {

		}
	}
}
Movie createMovie() {
	Movie temp; //������� ����� ��������� ��������� Movie
	cout << "Creating new Movie\nEnter name:" << endl;	
	getline(cin, temp.name); //����� �� ������ � �������� � name 
	cout << "Enter director: " << endl;
	getline(cin, temp.director); //����� �� ��������� ������ � ��������� � ���� director ���������� ��������� 
	cout << "Enter genre: " << endl;
	printMenuGenre();
	cin >> temp.genre;
	cout << "Enter rating (1-10): " << endl;
	cin >> temp.rate;
	cout << "Enter price: " << endl;
	cin >> temp.price;
	return temp;
}

Movie* createVideoCollection(int& size) {
	Movie* temp = new Movie[size];
	for (int i = 0; i < size; i++) {
		temp[i] = createMovie();
	}
	return temp;
}

void printMovie(Movie m) {//��������� ���� ������ ���������
	cout << "Name:     " << m.name << endl << "Director: " << m.director << endl << "Genre:    " << 
		printGenre(m.genre) << endl //� printGenre �������� int �������� ���� genre �������, ������� ���������� �����. ��������� �������� 
		<< "Rating:   " << m.rate << endl << "Price:    $" <<  m.price << "\n\n";	
}

void printAllMovies(Movie* movies, int &size) { //�������� ��������� �� ������ ��������-�������� � ������ �� ��� ������
	for (int i = 0; i < size; i++) { //� ����� � printMovie ���������� ���������� ������ ������ ��������� (�������)
		printMovie(movies[i]);
	}
	cout << endl;
}

Movie* addMovie(Movie* movies, int& size) {//� main ���������� ������� ������ ��� ����������� ��� ��������, � ��� ������
	Movie* temp = new Movie[++size]; //�������� ������ �� ����� ������ � ����������� ��������
	for (size_t i = 0; i < size - 1; i++) //size-1 ����� ��� �������� �� ����� �� ������� ����������� �������
	{
		temp[i] = movies[i]; //���������� �������� �������� ��������� ������� �� �������� � �����
	}
	temp[size - 1] = createMovie();//��� ������ [3] ������ [4], ���������� �������� ������� - [4-1] ����������� ��������� createMovie
	delete[] movies; //������� ������ ������
	return temp; //���������� ����� �� ������� � ������ �������, � ������ �������
}

//****����� ������ �� �����****//  
void searchMovieByName(Movie *&films, int size, string name) {
	
	Movie found; bool flag = false;
	for (int i = 0; i < size; i++)//� ����� ������� �� ���������� ��������
	{		
		if (films[i].name == name) {//���� ���� ������� �� �������� �������� ������� ������ �������� ����������			
			{
				found = films[i];					
			};
			flag = true;
			break;
		}			
	}	
	if (flag) {
		cout << "\nWe found: " << endl;
		printMovie(found);
	}
	else cout << "\nNo such movie in the collection :(" << endl;
}

void searchMoviesByGenre(Movie*& movies, int size, int genre, Movie*& outMovies, int& sizeOut) {
//��������� ������� ����������� ������ ��������, ��� ������, �������� enum �����, ���������� ������� ������ ��� ������, ��� ������ (�������)
	for (int i = 0; i < size; i++) {//���� ����������� ������� ������� � ������� ������
		if (movies[i].genre == genre) {
			++sizeOut;
		}
	}
	outMovies = new Movie[sizeOut]; //����������� �� ������ ������� (���������� � main) ����������� ����� ������ ������� �������
	for (int i = 0, j = 0; i < size; i++) {
		if (movies[i].genre == genre) {//� ������ ���������� ����� � ����� ������� � �������
			outMovies[j++] = movies[i]; //..���������� � ����� ������ ��������� �� �������, ������ �������������
		}
	}
}

//****����� ������ � ����������� ��������� � �����****//
Movie getTopFilmInGenre(Movie* films, int size, int genre) {//���������� ���������
	Movie* genreFilms = nullptr;//������ ������ ��� ����� ���������
	int sizeGenre = 0;
	searchMoviesByGenre(films, size, 0, genreFilms, sizeGenre);//��������� �����.������, ��� ������, ��������� ������ ������, ��� ������
	if (sizeGenre == 0) {//���� ������� ������� ����� �� ������� � ������ ������
		cout << "No films in genre";
	}
	else {
		Movie res = genreFilms[0];//���������� ��-�� ���� ��������� ��������� �������� ������� �� ���������� �� �����
		for (int i = 1; i < sizeGenre; i++)//� ����� ������� �� ���������� ��������
		{
			if (genreFilms[i].rate > res.rate) {//���� ���� ������� �� �������� �������� ������� ������ �������� ����������
				res = genreFilms[i]; //����������� ���������� �������� �������� ��������
			}
		}
		return res;//������� ��������� � ������������ ��������� ��������
	}
}

int main()
{	
	//****���������� ��������������� �������****//
	Movie f1 = { "The Godfather","F.F.Coppola", 0, 9.2, 50 }; //�������� ����������� �������� - ��������� ���������
	Movie f2 = { "Angry Man","S.Lumet", 1, 8.9, 40 };
	Movie f3 = { "Pulp Fiction","Q.Tarantino", 0, 8.9, 40 };
	int size = 3; //������� ��� �������� ������� ��������
	Movie* films = new Movie[size]{ f1,f2,f3 };//�������� ������ ��� ������������ ������ ���� Movie � �������������� ��� ����������� 

	//****���������� ��������� ������� ****//
	/*cout << "Enter the size of the collection: " << endl;
	cin >> size;	
	Movie* films = createVideoCollection(size);*/
	
	//****����� ��������������� �������****//	
	cout << "CURRENT COLLECTION: " << endl;
	printAllMovies(films, size); //����� �������������� ���������
			
	//****���������� ������ ������****//
	films = addMovie(films, size); //��������� �� ������ ��������� ��������� ��������� ������ addMovie
	cout << "\nUPDATED COLLECTION: " << endl;
	printAllMovies(films, size); //��������� ����� ����������

	//****����� ������ �� �����****//
	cout << "SEARCH MOVIE BY NAME:" << endl;
	string line;
	cout << "Please enter movie name: " << endl;
	while (cin.get() != '\n'); //���� �� ����� �������� ������� 
	getline (cin, line); //��������� � ���������� � ������
	searchMovieByName(films, size, line); //�������� ������, ������, ���
	
	
	//****����� ������� �� �����****//
	Movie* comedyFilms = nullptr; //������� ��������� �� ����� ������ ������������� �����
	int sizeComedy = 0; //�������������� ������
	cout << "\nFIND FILMS BY GENRE: " << endl;
	searchMoviesByGenre(films, size, Drama, comedyFilms, sizeComedy); /*��������� ������ ��������, ��� ������, enum ����� � int ���������, 
	��������� ������� ������ ��� ��������� ����, ��� ������ (�������)*/
	printAllMovies(comedyFilms, sizeComedy);
	
	//****����� ������ � ����������� ��������� � �����****//
	Movie top = getTopFilmInGenre(films, size, Drama); //��������� ������ ��������, ��� ������, �������� ����� � enum 
	cout << "TOP MOVIE IN GENRE " << '"' << printGenre(Drama) << '"' << ":" << endl;
	printMovie(top);
	delete[] films; //������������ ������������ ������ ��� ������
}