//Lesson 16: Создать структуру ВИДЕОМАГАЗИН со следующими
//полями:
// Название фильма; Режиссер; Жанр; Рейтинг популярности; Цена диска.
// Реализовать следующие возможности:
// Поиск по названию;
// Поиск по жанру;
// Поиск по режиссеру;
// Самый популярный фильм в жанре;
// Показ всех записей и добавление.
// Для реализации задачи используйте функции. Объекты структуры можно передавать в функцию целиком или отдельными полями.
// Выберите верный механизм передачи в каждом конкретном случае.


#include <iostream>
#include <string.h>
#include <string>
using namespace std;

enum genre { Drama, Comedy, Musical, Romance, RomanticСomedy, Detective, Action };
//перечисление с константами с значениями от 0 до 6

struct Movie { //структура единицы коллекции
	string name;
	string director;
	int genre;
	double rate;
	int price;	
};

string printGenre(int a) { //на переданный int возвращает строку в которую записывается значение из свича
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
	case RomanticСomedy:
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
	return s; //возвращаем строку с жанром
}
void printMenuGenre() { //вывод жанров - в цикле в printGenre передается значение от 0 до 6 и выводится соответ. строка
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
	Movie temp; //создаем новый экземпляр структуры Movie
	cout << "Creating new Movie\nEnter name:" << endl;	
	getline(cin, temp.name); //взять из потока и записать в name 
	cout << "Enter director: " << endl;
	getline(cin, temp.director); //взять из входящего потока и поместить в поле director экземпляра структуры 
	cout << "Enter genre: " << endl;
	printMenuGenre();
	cin >> temp.genre;
	cout << "Enter rating: " << endl;
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

void printMovie(Movie m) {//выводятся поля каждой структуры
	cout << "Name:     " << m.name << endl << "Director: " << m.director << endl << "Genre:    " << 
		printGenre(m.genre) << endl //в printGenre передаем int значение поля genre объекта, которая возвращает соотв. строковое значение 
		<< "Rating:   " << m.rate << endl << "Price:    $" <<  m.price << "\n\n";	
}

void printAllMovies(Movie* movies, int &size) { //передаем указатель на массив объектов-структур и ссылку на его размер
	for (int i = 0; i < size; i++) { //в цикле в printMovie поочередно передается каждый объект коллекции (массива)
		printMovie(movies[i]);
	}
	cout << endl;
}

Movie* addMovie(Movie* movies, int& size) {//в main передается текущий массив для копирования его значений, и его размер
	Movie* temp = new Movie[++size]; //выделяем память по новый массив с увеличенным размером
	for (size_t i = 0; i < size - 1; i++) //size-1 чтобы при итерации не выйти за пределы копируемого массива
	{
		temp[i] = movies[i]; //поочередно копируем значения элементов массива из текущего в новый
	}
	temp[size - 1] = createMovie();//был массив [3] теперь [4], последнему элементу массива - [4-1] присваиваем результат createMovie
	delete[] movies; //удаляем старый массив
	return temp; //возвращаем новый со старыми и новыми данными, с другим адресом
}

void searchMoviesByGenre(Movie*& movies, int size, int genre, Movie*& outMovies, int& sizeOut) {
//принимает текущий обновленный массив структур, его размер, значение enum жанра, переданный нулевой массив под фильмы, его размер (нулевой)
	for (int i = 0; i < size; i++) {//цикл определения размера массива с искомым жанром
		if (movies[i].genre == genre) {
			++sizeOut;
		}
	}
	outMovies = new Movie[sizeOut]; //переданному по ссылке массиву (созданному в main) присваиваем новый массив нужного размера
	for (int i = 0, j = 0; i < size; i++) {
		if (movies[i].genre == genre) {//в случае совпадения жанра в нашем массиве с искомым
			outMovies[j++] = movies[i]; //..записываем в новый массив структуру из старого, делаем постинкремент
		}
	}
}

Movie getTopFilmInGenre(Movie* films, int size, int genre) {//возвращает структуру
	Movie* genreFilms = nullptr;//пустой массив под новую коллекцию
	int sizeGenre = 0;
	searchMoviesByGenre(films, size, 0, genreFilms, sizeGenre);//принимает текущ.массив, его размер, созданный пустой массив, его размер
	if (sizeGenre == 0) {//если фильмов данного жанра не нашлось и массив пустой
		cout << "No films in genre";
	}
	else {
		Movie res = genreFilms[0];//временному эл-ту типа структура присвоить значение первого из отобранных по жанру
		for (int i = 1; i < sizeGenre; i++)//в цикле начиная со следующего элемента
		{
			if (genreFilms[i].rate > res.rate) {//если поле рейтинг из текущего элемента массива больше рейтинга временного
				res = genreFilms[i]; //присваивать временному элементу значения текущего
			}
		}
		return res;//вернуть структуру с максимальным значением рейтинга
	}
}

int main()
{
	Movie f1 = { "The Godfather","F.F.Coppola", 0, 9.2, 50 }; //создание экземпляров структур - элементов видеотеки
	Movie f2 = { "Angry Man","S.Lumet", 1, 8.9, 40 };
	Movie f3 = { "Pulp Fiction","Q.Tarantino", 0, 8.9, 40 };
	int size = 3; //размера для создания массива структур

	//****вывод первоначального массива****//
	Movie* films = new Movie[size]{ f1,f2,f3 };//выделяем память под динамический массив типа Movie и инициализируем его структурами 
	cout << "CURRENT COLLECTION: " << endl;
	printAllMovies(films, size); //вывод первоначальной коллекции
	
	//****добавление нового фильма****//
	films = addMovie(films, size); //указателю на массив коллекций присвоить результат работы addMovie
	cout << "\nUPDATED COLLECTION: " << endl;
	printAllMovies(films, size); //коллекция после добавления
	
	//****отбор фмльмов по жанру****//
	Movie* comedyFilms = nullptr; //нулевой указатель на новый массив определенного жанра
	int sizeComedy = 0; //первоначальный размер
	cout << "FIND FILMS BY GENRE: " << endl;
	searchMoviesByGenre(films, size, Drama, comedyFilms, sizeComedy); /*принимает массив структур, его размер, enum жанра с int значением, 
	созданный нулевой массив под выбранный жанр, его размер (нулевой)*/
	printAllMovies(comedyFilms, sizeComedy);

	//****поиск фильма с масимальным рейтингом в жанре****//
	Movie top = getTopFilmInGenre(films, size, Drama); //принимает массив структур, его размер, значение жанра в enum 
	cout << "TOP MOVIE IN GENRE " << printGenre(Drama) << ":" << endl;
	printMovie(top);
	delete[] films; //освобождение динамической памяти под массив
}