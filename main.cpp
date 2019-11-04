#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace sf;

const int WIDTH=600;
const int HEIGHT=480;

const int MAXN=1e5+100;
int n=10;

int sleep_t = 500000;

struct Building 
{ 
public:
    int left;  // x coordinate of left side 
    int ht;    // height 
    int right; // x coordinate of right side 

    bool operator <(const Building &p){
        if(left == p.left){
            if(ht == p.ht){
                return right < p.right;
            }
            return ht < p.ht;
        }
        return left < p.left;
    }
}; 
  
class Strip 
{ 
public: 
    int left;  // x coordinate of left side 
    int ht; // height 
    Strip(int l=0, int h=0) 
    { 
        left = l; 
        ht = h; 
    } 
    friend class SkyLine; 
}; 
  
class SkyLine 
{ 
public: 
    Strip *arr;   // Array of strips 
    int capacity; // Capacity of strip array 
    int n;   // Actual number of strips in array 
    ~SkyLine() {  delete[] arr;  } 
    int count()  { return n;   } 
  
    SkyLine* Merge(SkyLine *other); 
  
    SkyLine(int cap) 
    { 
        capacity = cap; 
        arr = new Strip[cap]; 
        n = 0; 
    } 
  
    void append(Strip *st) 
    { 
        if (n>0 && arr[n-1].ht == st->ht) 
            return; 
        if (n>0 && arr[n-1].left == st->left) 
        { 
            arr[n-1].ht = std::max(arr[n-1].ht, st->ht); 
            return; 
        } 
  
        arr[n] = *st; 
        n++; 
    } 
	void print() 
    { 
        for (int i=0; i<n; i++) 
        { 
            if(i) std::cout << " ";
            std::cout << "(" << arr[i].left << ", "
                 << arr[i].ht << "), "; 
        } 
        std::cout << std::endl;
    } 
  
}; 
  
SkyLine *findSkyline(Building arr[], int l, int h) 
{ 
    if (l == h) 
    { 
        SkyLine *res = new SkyLine(2); 
        res->append(new Strip(arr[l].left, arr[l].ht)); 
        res->append(new Strip(arr[l].right, 0)); 
        return res; 
    } 
  
    int mid = (l + h)/2; 
  
    SkyLine *sl = findSkyline(arr, l, mid); 
    SkyLine *sr = findSkyline(arr, mid+1, h); 
    SkyLine *res = sl->Merge(sr); 
  
    delete sl; 
    delete sr; 
  
    return res; 
} 

SkyLine *SkyLine::Merge(SkyLine *other) 
{ 
    SkyLine *res = new SkyLine(this->n + other->n); 
    int h1 = 0, h2 = 0; 
    int i = 0, j = 0; 
    while (i < this->n && j < other->n) 
    { 
        if (this->arr[i].left < other->arr[j].left) 
        { 
            int x1 = this->arr[i].left; 
            h1 = this->arr[i].ht; 
            int maxh = std::max(h1, h2); 
  
            res->append(new Strip(x1, maxh)); 
            i++; 
        } 
        else
        { 
            int x2 = other->arr[j].left; 
            h2 = other->arr[j].ht; 
            int maxh = std::max(h1, h2); 
            res->append(new Strip(x2, maxh)); 
            j++; 
        } 
    } 

    while (i < this->n) 
    { 
        res->append(&arr[i]); 
        i++; 
    } 
    while (j < other->n) 
    { 
        res->append(&other->arr[j]); 
        j++; 
    } 
    return res; 
} 

int main(int argc, char* argv[]){
	srand(time(NULL));
    if(argc >= 2){
		try{
			std::cout << "\n" << argv[1] << '\n' ;
			int s = atoi(argv[1]);
	
			if(s>=2 and s<=MAXN){
				n = s;
			}else{
				std::cout << "Numer of strucutres must be between 2 and "<< MAXN <<" . Using default." << std::endl;
			}
		}
		catch(...){
			std::cout << "Invalid argument was passed, number of strucutres must be an integer. Using default." << std::endl;
		}
	}
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SkyLine");
	auto desktop = VideoMode::getDesktopMode();
	Vector2i v2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
	window.setPosition(v2i);
	window.setFramerateLimit(60);

	Texture texture;
	texture.loadFromFile("background.jpg");
	Sprite sBackground(texture);

	Sprite sprite;
	RenderTexture t;
	t.create(WIDTH, HEIGHT);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(sBackground);
	window.draw(sprite);
	window.display();

	// int n=8;
    // Building arr[] = {{10, 11, 50}, {20, 6, 70}, {30, 13, 90}, 
    //                   {120, 7, 160}, {140, 3, 250}, {190, 18, 220}, 
    //                   {230, 130, 290}, {240, 4, 280}};
	Building arr[MAXN];
	for(int i=0; i<n; ++i){
		int l=rand()%WIDTH;
		int r=rand()%WIDTH;
		if(l==r) l++, l%=WIDTH;
		else if(l>r) std::swap(l, r);
		arr[i] = Building {l, rand()%HEIGHT, r};
	}

    Sprite temp_sprite;
	RenderTexture temp_t;
	temp_t.create(WIDTH, HEIGHT);
	temp_t.setSmooth(true);
	temp_sprite.setTexture(temp_t.getTexture());

    VertexArray buildings(LinesStrip, 4);
    for(int i=0; i<n; ++i){
        buildings[0].position = Vector2f(arr[i].left, HEIGHT);
        buildings[1].position = Vector2f(arr[i].left, HEIGHT-arr[i].ht);
        buildings[2].position = Vector2f(arr[i].right, HEIGHT-arr[i].ht);
        buildings[3].position = Vector2f(arr[i].right, HEIGHT);

        temp_t.draw(buildings);
        temp_t.display();
    }
    window.draw(temp_sprite);
    window.display();

    std::sort(arr, arr+n);
	SkyLine *ptr = findSkyline(arr, 0, n-1);
	std::cout << " Skyline for given buildings is \n"; 
    ptr->print();

    usleep(5*sleep_t);
    window.clear();

    auto aux = ptr->arr;
    int last = ptr->n;
    auto curr = aux[0];
    int pos=0;
    VertexArray lines(Lines, 2);
    lines[0].position = Vector2f(curr.left, HEIGHT);
    lines[1].position = Vector2f(curr.left, HEIGHT-curr.ht);

    t.draw(lines);
    t.display();
    window.draw(sprite);
	window.display();
	while(window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if(e.type == Event::Closed){
				window.close();
			}
		}
        if(pos==last-1) continue;
        auto next = aux[++pos];
        lines[0].position = Vector2f(curr.left, HEIGHT-curr.ht);
        lines[1].position = Vector2f(next.left, HEIGHT-curr.ht);
        t.draw(lines);
        t.display();
        usleep(sleep_t);
        window.clear();
		window.draw(sprite);
		window.display();
        lines[0].position = Vector2f(next.left, HEIGHT-next.ht);
        lines[1].position = Vector2f(next.left, HEIGHT-curr.ht);
        
        t.draw(lines);
        t.display();
        curr = next;
        usleep(sleep_t);
		window.clear();
		window.draw(sprite);
		window.display();
	}

}
