#include<bits/stdc++.h>
using namespace std;

class Area{

private:
    int side,length,breadth,radius;
    friend class Volume;

public:
    void setSide(int side){
        this->side = side;
    }
    void setLengthBreadth(int length,int breadth){
        this->length = length;
        this->breadth = breadth;
    }
    void setRadius(int radius){
        this->radius = radius;
    }
    int Square_Area();
    int Rectangle_Area();
    float Circle_Area();
};

inline int Area :: Square_Area(){
    return side*side;
}

inline int Area :: Rectangle_Area(){
    return length*breadth;
}

inline float Area :: Circle_Area(){
    return 3.14*radius*radius;
}

class Volume: public Area{

private:
    int height;

public:
    Volume(){
        side = 1;
        length = 1;
        breadth = 1;
        radius = 1;
        height = 1;
    }
    void setHeight(int height){
        this->height = height;
    }
    int CubeVol(Volume Obj);
    int CuboidVol(Volume Obj);
    float SphereVol(Volume Obj);
};

inline int Volume :: CubeVol(Volume obj) {
    return obj.Square_Area()*side;
}

inline int Volume :: CuboidVol(Volume obj){
    return obj.Rectangle_Area()*height;
}

inline float Volume :: SphereVol(Volume obj){
    return obj.Circle_Area()*radius*4/3.0;
}

void display(){
    cout << "1. Area of Square" << endl;
    cout << "2. Area of Rectangle" << endl;
    cout << "3. Area of Circle" << endl;
    cout << "4. Volume of Cube" << endl;
    cout << "5. Volume of Cuboid" << endl;
    cout << "6. Volume of Sphere" << endl;
    cout << "7. Compare Cubes" << endl;
    cout << "8. Compare Cuboids" << endl;
    cout << "9. Compare Spheres" << endl;
    cout << "10. To visit previous menu" << endl;
}

int main(){
    int choice;
    int count=0,c=0,cu=0,s=0;
    Volume array[100];
    vector <int> v1,v2;
    while(1) {
        cout << "1. To enter dimensions" << endl;
        cout << "2. To take default inputs" << endl;
        cout << "3. To exit" << endl;
        cin >> choice;
        if (choice == 1) {
            int side,length,breadth,radius,height;
            Volume obj = Volume();
            count++;
            display();
            while (true) {
                int n;
                cout << "Enter your choice: ";
                cin >> n;
                int flag = -123;
                switch (n) {
                    case 1:
                        cout << "Enter side of square: ";
                        cin >> side;
                        obj.setSide(side);
                        cout << "Area of Square : " << obj.Square_Area() << endl;
                        break;
                    case 2:
                        cout << "Enter Length of Rectangle : ";
                        cin >> length;
                        cout << "Enter Breadth of Rectangle : ";
                        cin >> breadth;
                        obj.setLengthBreadth(length, breadth);
                        cout << "Area of Rectangle: " << obj.Rectangle_Area() << endl;
                        break;
                    case 3:
                        cout << "Enter Radius of circle: ";
                        cin >> radius;
                        obj.setRadius(radius);
                        cout << "Area of Circle : " << obj.Circle_Area() << endl;
                        break;
                    case 4:
                         cout << "Enter side of cube: ";
                        cin >> side;
                        obj.setSide(side);
                        c++;
                        cout << "Volume of Cube: " << obj.CubeVol(obj) << endl;
                        if(count==1)
                            v1.push_back(obj.CubeVol(obj));
                        else
                            v2.push_back(obj.CubeVol(obj));
                        break;
                    case 5:
                        cu++;
                        cout << "Enter Length of cuboid : ";
                        cin >> length;
                        cout << "Enter Breadth of cuboid : ";
                        cin >> breadth;
                        obj.setLengthBreadth(length, breadth);
                        cout << "Enter Height of cuboid : ";
                        cin >> height;
                        obj.setHeight(height);
                        cout << "Volume of Cuboid : " << obj.CuboidVol(obj) << endl;
                        if(count==1)
                            v1.push_back(obj.CuboidVol(obj));
                        else
                            v2.push_back(obj.CuboidVol(obj));
                       
                        break;
                    case 6:
                        s++;
                        cout << "Enter Radius of Sphere: ";
                        cin >> radius;
                        obj.setRadius(radius);
                        cout << "Volume of Sphere : " << obj.SphereVol(obj) << endl;
                        if(count==1)
                            v1.push_back(obj.SphereVol(obj));
                        else
                            v2.push_back(obj.SphereVol(obj));
                        break;
                    case 7:
                        
                        if(count==1) {
                            if (c==0)
                                cout << " Find cube volume to compare and try again\n";
                            else
                            cout << "Larger Cube  has volume  : " << v1[0] << endl;
                        }
                        else{
                            cout << "Larger Cube has volume   : ";
                            if(v1[0] > v2[0])
                                cout << v1[0] << endl;
                            else if(v1[0]<v2[0])
                                cout << v2[0] << endl;
                            else
                            cout << "Both have same volumes\n";
                        }
                        break;
                    case 8 :
                        if(count==1){
                            if (cu==0)
                                cout << " Find cuboid volume to compare and try again\n";
                            else
                            cout << "Larger Cuboid has volume : " << v1[1] << endl;
                        }
                        else{
                            cout << "Larger Cuboid volume : ";
                            if(v1[1] > v2[1])
                                cout << v1[1] << endl;
                            else if(v1[1]<v2[1])
                                cout << v2[1] << endl;
                            else
                              cout << "Both have same volume\n";
                        }
                        break;
                    case 9 :
                        if(count==1){
                            if (s==0)
                                cout << " Find sphere volume to compare and try again\n";
                            else
                            cout << "Larger Sphere has volume : " << v1[2] << endl;
                        }
                        else
                            {
                            cout << "Larger Sphere has volume: ";
                            if(v1[2] > v2[2])
                                cout << v1[2] << endl;
                            else if (v1[2]<v2[2])
                                cout << v2[2] << endl;
                            else
                            cout << "Both have same volume\n";
                        }
                        break;
                    case 10:
                        flag = 1;
                        break;
                }
                if (flag == 1) {
                    break;
                }
            }
        }
        else if(choice == 2){
            Volume obj = Volume();
            array[count] = obj;
            count++;
            display();
            while (true) {
                int n;
                cout << "Enter your choice : ";
                cin >> n;
                int flag = -123;
                switch (n) {
                    case 1:
                        cout << "Area of Square : " << obj.Square_Area() << endl;
                        break;
                    case 2:
                        cout << "Area of Rectangle: " << obj.Rectangle_Area() << endl;
                        break;
                    case 3:
                        cout << "Area of Circle : " << obj.Circle_Area() << endl;
                        break;
                    case 4:
                        cout << "Volume of Cube: " << obj.CubeVol(obj) << endl;
                        break;
                    case 5:
                        cout << "Volume of Cuboid : " << obj.CuboidVol(obj) << endl;
                        break;
                    case 6:
                        cout << "Volume of Sphere : " << obj.SphereVol(obj) << endl;
                        break;
                    case 7 :
                        cout << "Larger Cube has volume : " << obj.CubeVol(obj) << endl;
                        break;
                    case 8:
                        cout << "Larger Cuboid has volume: " << obj.CuboidVol(obj) << endl;
                        break;
                    case 9:
                        cout << "Larger Sphere has volume : " << obj.SphereVol(obj) << endl;
                        break;
                    case 10:
                        flag = 1;
                        break;
                }
                if (flag == 1) {
                    break;
                }
            }
        }
        else{
            return 0;
        }
    }
}