//aurthor chaobo wu

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

class Vec3d{
public:
    double x,y,z;
    Vec3d(double x,double y,double z):x(x),y(y),z(z){}

  /*  ostream&operator<<(ostream&out,Vec3d&v1){
        out<<"("<<v1.x <<v1.y <<v1.z<<")\n";
        return out;
    }*/
};

Vec3d normal(const Vec3d v1,const Vec3d v2){
    Vec3d result(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.y,v1.x*v2.y-v1.y*v2.x);
    return result;
}


class Shape {
private:
    double x,y,z;
public:
    virtual string option(){};
    Shape(double x,double y,double z):x(x),y(y),z(z){
    }
    double getx(){
        return x;
    }
    double gety(){
        return y;
    }
    double getz(){
        return z;
    }
};

class Cube: public Shape {
private:
    double size;
public:
    string option(){
        return ("Cube");
    }
    Cube(double x, double y, double z, double size) : size(size), Shape(x,y,z){}
    double getsize(){
        return size;
    }
    friend ofstream &operator<<(ofstream&out,Cube&cube);
};

ofstream &operator<<(ofstream&out,Cube&cube){
    double x_ori=cube.getx();
    double y_ori=cube.gety();
    double z_ori=cube.getz();
    double size=cube.getsize();

    Vec3d vt(0.0,0.0,-1.0);
//        Vec3d normal_t();
    for(int i=0;i<=270;i+=90){
        double x_t = cos((double) i / 180 * M_PI);
        double y_t = sin((double) i / 180 * M_PI);
        for(int j=0;j<=1;j++) {
            Vec3d v1(x_t, y_t, 0.0);
            Vec3d normal_t = normal(v1, vt);
            out << "  facet normal " << normal_t.x << ' ' << normal_t.y << ' ' << normal_t.z << "\n";
            out << "    outer loop\n";
            if (j) {
                out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori << "\n";
                out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori + size << "\n";
                out << "      vertex " << x_ori + size*x_t << ' ' << y_ori+size*y_t << ' ' << z_ori + size << "\n";
            }
            else {
                out << "      vertex " << x_ori + size*x_t << ' ' << y_ori+size*y_t << ' ' << z_ori + size << "\n";
                out << "      vertex " << x_ori + size*x_t << ' ' << y_ori+size*y_t << ' ' << z_ori << "\n";
                out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori  << "\n";
            }
            out << "    endloop\n";
            out << "  endfacet\n";

        }
        x_ori+=size*x_t;
        y_ori+=size*y_t;

    }
    out << "  facet normal " << 0 << ' ' << 0 << ' ' << 1 << "\n";
    out << "    outer loop\n";
    out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori +size<< "\n";
    out << "      vertex " << x_ori+size << ' ' << y_ori+size << ' ' <<  z_ori+size << "\n";
    out << "      vertex " << x_ori + size<< ' ' << y_ori << ' ' << z_ori + size << "\n";
    out << "    endloop\n";
    out << "  endfacet\n";

    out << "  facet normal " << 0 << ' ' << 0 << ' ' << 1 << "\n";
    out << "    outer loop\n";
    out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori +size<< "\n";
    out << "      vertex " << x_ori << ' ' << y_ori+size << ' ' <<  z_ori+size << "\n";
    out << "      vertex " << x_ori + size<< ' ' << y_ori+size << ' ' << z_ori + size << "\n";
    out << "    endloop\n";
    out << "  endfacet\n";

    out << "  facet normal " << 0 << ' ' << 0 << ' ' << -1 << "\n";
    out << "    outer loop\n";
    out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori << "\n";
    out << "      vertex " << x_ori +size<< ' ' << y_ori << ' ' <<  z_ori<< "\n";
    out << "      vertex " << x_ori + size<< ' ' << y_ori+size << ' ' << z_ori << "\n";
    out << "    endloop\n";
    out << "  endfacet\n";

    out << "  facet normal " << 0 << ' ' << 0 << ' ' << -1 << "\n";
    out << "    outer loop\n";
    out << "      vertex " << x_ori << ' ' << y_ori << ' ' << z_ori << "\n";
    out << "      vertex " << x_ori +size<< ' ' << y_ori+size << ' ' <<  z_ori<< "\n";
    out << "      vertex " << x_ori << ' ' << y_ori+size << ' ' << z_ori << "\n";
    out << "    endloop\n";
    out << "  endfacet\n";
}

class Cylinder : public Shape{
private:
    double r, h;
    int facets;
public:
    Cylinder(double x, double y, double z, double r, double h, int facets) :Shape(x,y,z),r(r),h(h),facets(facets){}
    string option(){
        return ("Cylinder");
    }
    double geth(){
        return h;
    }
    double getr(){
        return r;
    }
    int getfacets(){
        return facets;
    }
    friend ofstream &operator<<(ofstream&out,Cylinder&cylinder);
};

ofstream &operator<<(ofstream&out,Cylinder&cylinder){
    double x_ori=cylinder.getx();
    double y_ori=cylinder.gety();
    double z_ori=cylinder.getz();
    double r=cylinder.getr();
    double h=cylinder.geth();
    int facets=cylinder.getfacets();
    double angle=360.0/facets;
    double x1,y1,x2,y2;
    double height=z_ori+h;
    Vec3d vt(0.0,0.0,1.0);
    for(int i=0;i<facets;i++){
        x1=x_ori+r*cos(angle*i / 180 * M_PI);
        y1=y_ori+r*sin(angle*i / 180 * M_PI);
        x2=x_ori+r*cos(angle*(i+1) / 180 * M_PI);
        y2=y_ori+r*sin(angle*(i+1) / 180 * M_PI);
        Vec3d temp(x2-x1,y2-y1,0.0);
        Vec3d normal_t=normal(vt,temp);

        out << "  facet normal " << 0.0 << ' ' << 0.0 << ' ' << 1.0 << "\n";
        out << "    outer loop\n";
        out << "      vertex " << x_ori<<' '<<y_ori<<' '<<height<<"\n";
        out << "      vertex " << x2<<' '<<y2<<' '<<height<<"\n";
        out << "      vertex " << x1<<' '<<y1<<' '<<height<<"\n";
        out << "    endloop\n";
        out << "  endfacet\n";

        out << "  facet normal " << 0.0 << ' ' << 0.0 << ' ' << -1.0 << "\n";
        out << "    outer loop\n";
        out << "      vertex " << x_ori<<' '<<y_ori<<' '<<z_ori<<"\n";
        out << "      vertex " << x2<<' '<<y2<<' '<<z_ori<<"\n";
        out << "      vertex " << x1<<' '<<y1<<' '<<z_ori<<"\n";
        out << "    endloop\n";
        out << "  endfacet\n";

        for(int j=0;j<2;j++){
            out << "  facet normal " << normal_t.x << ' ' << normal_t.y << ' ' << normal_t.z << "\n";
            out << "    outer loop\n";
            if(j){
                out << "      vertex " << x1<<' '<<y1<<' '<<0.0<<"\n";
                out << "      vertex " << x1<<' '<<y1<<' '<<height<<"\n";
                out << "      vertex " << x2<<' '<<y2<<' '<<height<<"\n";
            }
            else{
                out << "      vertex " << x2<<' '<<y2<<' '<<height<<"\n";
                out << "      vertex " << x2<<' '<<y2<<' '<<0.0<<"\n";
                out << "      vertex " << x1<<' '<<y1<<' '<<0.0<<"\n";

            }
            out << "    endloop\n";
            out << "  endfacet\n";

        }
    }

}

class CAD {
private:
    vector<Shape*> shapes;
public:
    void add(Shape* shape);
    void write(const string filename);
};

void CAD::add(Shape *shape) {
    shapes.push_back(shape);
}

void CAD::write(const string filename) {
    ofstream file(filename);
    file << "solid OpenSCAD_Model\n";
    for(auto s : shapes){
        if(s->option()=="Cube")
            file<<(Cube&)(*s);
        if(s->option()=="Cylinder")
            file<<(Cylinder&)(*s);
    }
    file << "endsolid OpenSCAD_Model\n";
    file.close();
}

int main() {
    CAD c;
    c.add(new Cube(0,0,0,   5));
    c.add(new Cylinder(100,0,0,    3, 10, 10));
    c.write("chaobowu.stl");
}