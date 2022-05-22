#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <stack>
#include <string>
#include <vector>


struct Point{
    float x;
    float y;
    float z;
    Point(float x_, float y_, float z_){
        x = x_;
        y = y_;
        z = z_;
    }
    Point() = default;
};

struct PointsComp{
    bool operator()(const Point& one, const Point& two) const {
        if (one.z == two.z){
            if (one.y == two.y){
                return one.x < two.x;
            }
            return one.y < two.y;
        }
        return one.z < two.z;
    }
};

bool comp(const Point& one, const Point& two) {
    if (one.z == two.z){
        if (one.y == two.y){
            return one.x < two.x;
        }
        return one.y < two.y;
    }
    return one.z < two.z;
};
struct Edge{
    Point from;
    Point to;
    Edge() = default;
    Edge(Point f, Point t){
        if (comp(f, t)){
            from = f;
            to = t;
        }
        else{
            from = t;
            to = f;
        }
    }
};

struct EdgesComp{
    bool operator()(const Edge& one, const Edge& two){
        if (one.from.x == two.from.x && one.from.y == two.from.y && one.from.z == two.from.z){
            return comp(one.to, two.to);
        }
        return comp(one.from, two.from);
    }
};

struct Plane{
    Point point;
    Point vector_normal;
    Point plane_as_points[3];
    Plane() = default;
    Plane(Point p, Point v){
        point = p;
        vector_normal = v;
    }
    Plane(Point p, float A, float B, float C){
        point = p;
        vector_normal = Point(A, B, C);
    }
    Plane(float x0, float y0, float z0, float A, float B, float C){
        point = Point(x0, y0, z0);
        vector_normal = Point(A, B, C);
    }
    Plane(Point p, Point v, Point a, Point b, Point c){
        point = p;
        vector_normal = v;
        if (comp(a, b)){
            if (comp(a, c)){
                plane_as_points[0] = a;
                if (comp(b, c)){
                    plane_as_points[1] = b;
                    plane_as_points[2] = c;
                }
                else{
                    plane_as_points[1] = c;
                    plane_as_points[2] = b;
                }
            }
            else{
                plane_as_points[0] = c;
                plane_as_points[2] = b;
                plane_as_points[1] = a;
            }
        }
        else{
            if (comp(b, c)){
                plane_as_points[0] = b;
                if (comp(a, c)){
                    plane_as_points[1] = a;
                    plane_as_points[2] = c;
                }
                else{
                    plane_as_points[1] = c;
                    plane_as_points[2] = a;
                }
            }
            else{
                plane_as_points[0] = c;
                plane_as_points[1] = b;
                plane_as_points[2] = a;
            }
        }
    }
};

struct EdgeWithPlane{
    Edge edge;
    Plane plane;
    EdgeWithPlane(Edge e, Plane p){
        edge = e;
        plane = p;
    }
};


struct SphereAngleAndDistance{
    float r;
    float thetha;
    float fi;
    float distance;
    SphereAngleAndDistance(float r_, float t_, float f_, float d_){
        r = r_;
        thetha = t_;
        fi = f_;
        distance = d_;
    }
};

bool AreEqual(const Point& one, const Point& two){
    return one.x == two.x && one.y == two.y && one.z == two.z;
}

struct ComparePlanes {
    bool operator()(const Plane& one, const Plane& two) const {
        /*if (one.vector_normal.z == two.vector_normal.z){
            if (one.vector_normal.y == two.vector_normal.y){
                return one.vector_normal.x < two.vector_normal.x;
            }
            return one.vector_normal.y < two.vector_normal.y;
        }
        return one.vector_normal.z < two.vector_normal.z;*/
        if (AreEqual(one.plane_as_points[0], two.plane_as_points[0])){
            if (AreEqual(one.plane_as_points[1], two.plane_as_points[1])){
                return comp(one.plane_as_points[2], two.plane_as_points[2]);
            }
            return comp(one.plane_as_points[1], two.plane_as_points[1]);
        }
        return comp(one.plane_as_points[0], two.plane_as_points[0]);
    }
};

float Distance(Point& from, Point& to){
    float x = to.x - from.x;
    float y = to.y - from.y;
    float z = to.z - from.z;
    return std::sqrt(x*x + y*y + z*z);
}

bool CompareForMin(const Point& one, const Point& two){
    return one.y < two.y;
}

class CloudTriangulation{
public:
    CloudTriangulation(std::string filename){
        /*std::ifstream file;
        file.open(filename);
        float x, y, z;
        float x_middle = 0;
        float y_middle = 0;
        float z_middle = 0;
        int count = 0;
        while (file >> x >> y >> z){
            shell.push_back(Point(x, y, z));
            x_middle+=x;
            y_middle+=y;
            z_middle+=z;
            count++;
        }
        x_middle/=count;
        y_middle/=count;
        z_middle/=count;
        for (int i=0; i<shell.size(); ++i){
            shell[i].x-=x_middle;
            shell[i].y-=y_middle;
            shell[i].z-=z_middle;
        }
        center = Point(x_middle, y_middle, z_middle);*/

        shell = {
                Point(-2.82, 0, 0),

                Point(-2, -1, 0),
                Point(-2, -0.5, -0.5),
                Point(-2, 0, -1),
                Point(-2, 0.5, -0.5),
                Point(-2, 1, 0),
                Point(-2, 0.5, 0.5),
                Point(-2, 0, 1),
                Point(-2, -0.5, 0.5),


                Point(0, -2, 0),
                Point(0, -0.5, -0.5),
                Point(0, 0, -2),
                Point(0, 0.5, -0.5),
                Point(0, 2, 0),
                Point(0, 0.5, 0.5),
                Point(0, 0, 2),
                Point(0, -0.5, 0.5),

                Point(2, -1, 0),
                Point(2, -0.5, -0.5),
                Point(2, 0, -1),
                Point(2, 0.5, -0.5),
                Point(2, 1, 0),
                Point(2, 0.5, 0.5),
                Point(2, 0, 1),
                Point(2, -0.5, 0.5),

                Point(2.82, 0, 0),
        };
    }
    void CountPolarAngle(int i, int j, SphereAngleAndDistance& param){
        float x = cloud[i].x - cloud[j].x;
        float y = cloud[i].y-cloud[j].y;
        float z = cloud[i].z-cloud[j].z;
        param = SphereAngleAndDistance(std::sqrt(x*x+y*y+z*z), std::atan(std::sqrt(x*x+y*y)/z), std::atan(y/x), std::sqrt(x*x+y*y+z*z));
    }
    Plane FindPlane(EdgeWithPlane& base){
        float min_cos = 2;
        Point min_item;
        Plane beta;
        for (int i=0; i<cloud.size(); ++i){//auto item = cloud_copy.begin(); item != cloud_copy.end(); ++item){
            Point M = base.edge.from;
            Point N = base.edge.to;
            float A = (M.y - cloud[i].y)*(N.z - cloud[i].z) - (N.y - cloud[i].y)*(M.z - cloud[i].z);//(M.y - item->y)*(N.z - item->z) - (N.y - item->y)*(M.z - item->z);
            float B = -1*(M.x - cloud[i].x)*(N.z - cloud[i].z) + (N.x - cloud[i].x)*(M.z - cloud[i].z);//-(M.x - item->x)*(N.z - item->z) + (N.x - item->x)*(M.z - item->z);
            float C = (M.x - cloud[i].x)*(N.y - cloud[i].y) - (N.x - cloud[i].x)*(M.y - cloud[i].y);//(M.x - item->x)*(N.y - item->y) - (N.x - item->x)*(M.y - item->y);

            float A1 = base.plane.vector_normal.x;
            float B1 = base.plane.vector_normal.y;
            float C1 = base.plane.vector_normal.z;

            if (A1*(cloud[i].x - base.plane.point.x)+B1*(cloud[i].y - base.plane.point.y)+C1*(cloud[i].z - base.plane.point.z) == 0){
                continue;
            }


            /*float D = -A*cloud[i].x - B*cloud[i].y - C*cloud[i].z;
            float coef = A*(center.x - cloud[i].x) + B*(center.y-cloud[i].y)+C*(center.z-cloud[i].z) + D;
            //if plane lower than center
            if ( coef > 0){
                if (B<0) {
                    A *= -1;
                    B *= -1;
                    C *= -1;
                }
            }
            //if plane higher than center
            else if (coef < 0){
                if (B>0) {
                    A *= -1;
                    B *= -1;
                    C *= -1;
                }
            }*/

           // A(x-x0)+B(y-y0)+C(z-z0)=0
           // x:y:z = A:B:C
           // A(x+tA-x0)+B(y+tB-y0)+C(z+tC-z0)=0
           // t(A^2+B^2+C^2) = Ax0+By0+Cz0 - Ax-By-Cz
           // projection = x+tA, y+tB, z+tC

           float D = -A*cloud[i].x - B*cloud[i].y-C*cloud[i].z;
           float t = -(A*center.x + B*center.y  + C*center.z + D)/(A*A+B*B+C*C);
           //Point center_projection_param = Point(center.x+t*A, center.y+t*B, center.z+t*C);
           if (t < 0){//under center
               if (B <0){
                   A*=-1;
                   B*=-1;
                   C*=-1;
               }
           }
           else if (t > 0){
               if (B > 0){
                   A*=-1;
                   B*=-1;
                   C*=-1;
               }
           }


            float between_cos = (A1*A + B1*B + C1*C)/(std::sqrt(A*A+B*B+C*C)*std::sqrt(A1*A1+B1*B1+C1*C1));
            if ((between_cos == min_cos &&
                (Distance(N, cloud[i]) > Distance(N, min_item) || Distance(M, cloud[i]) > Distance(M, min_item)))
                || (between_cos<min_cos)){
                min_cos = between_cos;
                min_item = cloud[i];
                beta = Plane(cloud[i], Point(A, B, C), M, N, cloud[i]);
            }
        }
        //cloud_copy.erase(min_item);
        return beta;
    }
    void BuildShell(){
        std::sort(cloud.begin(), cloud.end(), comp);
        Point min = cloud[0];
        int current_i=0;
        shell.push_back(min);

        std::stack<EdgeWithPlane> edges_stack;
        std::set<Plane, ComparePlanes> found_planes;
        std::set<Point> shell_points;


        //build plane, parallel OXY throw min
        Plane plane(min, 0, 0, 1);
        float rand_x = std::rand() % 5;
        float rand_y = std::rand() % 7;
        float z  = min.z;
        Point M(min.x + rand_x, min.y + rand_y, z);

        Point collinear_vector(rand_x, rand_y, 0);
        float t = std::rand()%10*0.1;
        Point N(min.x-t*collinear_vector.x, min.y-t*collinear_vector.y, min.z);

        //now we have 3 points and can build a plane
        float min_cos = 2;
        int min_index = -1;
        Plane beta;

        for (int i=1; i<cloud.size(); ++i){
            //let 0 - from cloud, 1 - M, 2 - N
            // A(x-x0) = (y1-y0)(z2-z1)-(y2-y1)(z1-z0)
            float A = (M.y - cloud[i].y)*(N.z - cloud[i].z) - (N.y - cloud[i].y)*(M.z - cloud[i].z);
            float B = -(M.x - cloud[i].x)*(N.z - cloud[i].z) + (N.x - cloud[i].x)*(M.z - cloud[i].z);
            float C = (M.x - cloud[i].x)*(N.y - cloud[i].y) - (N.x - cloud[i].x)*(M.y - cloud[i].y);

            float A1 = plane.vector_normal.x;
            float B1 = plane.vector_normal.y;
            float C1 = plane.vector_normal.z;

            float between_cos = (A1*A + B1*B + C1*C)/(std::sqrt(A*A+B*B+C*C)*std::sqrt(A1*A1+B1*B1+C1*C1));
            if (between_cos<min_cos){
                min_cos = between_cos;
                min_index = i;
                beta = Plane(cloud[i], A, B, C);
            }
        }
        shell.push_back(cloud[min_index]);
        cloud_copy.erase(cloud[min_index]);
        current_i = min_index;

        //now build 3rd plane
        min_cos = 2;
        min_index = -1;
        Plane gamma;
        for (int i=1; i<cloud.size(); ++i){
            if (i==current_i){
                continue;
            }
            //let 0 - from cloud, 1 - M, 2 - N
            // A(x-x0) = (y1-y0)(z2-z1)-(y2-y1)(z1-z0)
            float A = (cloud[current_i].y - cloud[0].y)*(cloud[i].z - cloud[0].z) - (cloud[i].y-cloud[0].y)*(cloud[current_i].z - cloud[0].z);
            float B = -(cloud[current_i].x - cloud[0].x)*(cloud[i].z - cloud[0].z) + (cloud[i].z-cloud[0].z)*(cloud[current_i].z - cloud[0].z);
            float C = (cloud[current_i].x - cloud[0].x)*(cloud[i].y - cloud[0].y) - (cloud[i].x-cloud[0].x)*(cloud[current_i].y - cloud[0].y);

            float A1 = beta.vector_normal.x;
            float B1 = beta.vector_normal.y;
            float C1 = beta.vector_normal.z;

            float between_cos = (A1*A + B1*B + C1*C)/(std::sqrt(A*A+B*B+C*C)*std::sqrt(A1*A1+B1*B1+C1*C1));
            if (between_cos<=min_cos){
                min_cos = between_cos;
                min_index = i;
                gamma = Plane(cloud[i], A, B, C);
            }
        }
        shell.push_back(cloud[min_index]);
        cloud_copy.erase(cloud[min_index]);


        float A = (shell[1].y - shell[0].y)*(shell[2].z - shell[0].z) - (shell[2].y - shell[0].y)*(shell[1].z - shell[0].z);
        float B = -1*(shell[1].x - shell[0].x)*(shell[2].z - shell[0].z) + (shell[2].x - shell[0].x)*(shell[1].z - shell[0].z);
        float C = (shell[1].x - shell[0].x)*(shell[2].y - shell[0].y) - (shell[2].x - shell[0].x)*(shell[1].y - shell[0].y);
        Plane common_plane(cloud[0], Point(A, B, C), shell[0], shell[1], shell[2]);
        found_planes.insert(common_plane);
        edges_stack.push(EdgeWithPlane(Edge(cloud[0], shell[1]), common_plane));
        edges_stack.push(EdgeWithPlane(Edge(shell[1], cloud[min_index]), common_plane));
        edges_stack.push(EdgeWithPlane(Edge(cloud[0], cloud[min_index]), common_plane));

        //now we ready to build it all
        while (!edges_stack.empty()){
            EdgeWithPlane e = edges_stack.top();
            edges_stack.pop();
            Plane beta = FindPlane(e);
            if (found_planes.find(beta) == found_planes.end()){

                found_planes.insert(beta);
                edges_stack.push(EdgeWithPlane(Edge(beta.point, e.edge.from), beta));
                edges_stack.push(EdgeWithPlane(Edge(beta.point, e.edge.to), beta));
                shell.push_back(beta.point);
            }
        }
        std::ofstream file;
        file.open("shell.txt");
        for (int i=0; i<shell.size(); ++i){
            file<<shell[i].x<<" "<<shell[i].y<<" "<<shell[i].z<<"\n\r";
        }
        file.close();
    }


    bool static ComparePointsForShell (const Point &one, const Point &two){
        if (one.x == two.x) {
            if (one.z < 0 && two.z > 0 || (one.z > 0 && two.z < 0)){
                return one.z < 0;
            };
            if (one.z == 0){
                if (two.z > 0){
                    return true;
                }
                else {
                    return one.y < two.y;
                }
            }
            if (two.z == 0){
                if (one.z > 0) {
                    return false;
                }
                else{
                    return one.y < two.y;
                }
            }


            if (one.y == two.y){
                if (one.z == 0){
                    return two.z>0;
                }
                if (two.z == 0){
                    return one.z <0;
                }
                if (one.z < 0 && two.z > 0 || (one.z > 0 && two.z < 0)){
                    return one.z < 0;
                }
                return std::abs(one.z) < std::abs(two.z);
            }

            if (one.y < two.y){
                return one.z <=0;
            }
            if (one.y > two.y){
                return one.z>=0;
            }

            /*if (one.z == two.z){
                return one.y < two.y;
            }
            if (one.z == 0 || two.z == 0){
                return one.z < two.z;
            }
            if (one.z < 0 && two.z > 0 || (one.z > 0 && two.z < 0)){
                return one.z < 0;
            }
            if (one.z<0) {//means they both <0
                return one.y < two.y;//include III and II 1/4 of circle
            }
            else{
                return one.y > two.y;//include I and IV 1/4 of circle
            }*/
        }
        return one.x < two.x;
    };

    void BuildTriangulation(){
        std::sort(shell.begin(), shell.end(), ComparePointsForShell);

        //RecurcionTriangulation(0, shell.size()-1, y, result);

        //start triangul
        int prev_x_plane_start_index = 1;
        float current_x_plane = shell[1].x;
        triangulation.push_back(Edge(shell[0], shell[1]));
        int i=2;
        while(shell[i].x == current_x_plane){
            triangulation.push_back(Edge(shell[i-1], shell[i]));
            triangulation.push_back(Edge(shell[0], shell[i]));
            ++i;
        }
        if (shell[i-1].x == shell[1].x && i!=2) {
            triangulation.push_back(Edge(shell[1], shell[i-1]));
        }

        //we prepared start. Now let's make a cycle

        current_x_plane = shell[i].x;

        int left_idx = 1;
        int right_idx = i;
        int start_left_idx = left_idx;
        int start_right_idx = right_idx;
        //let's suppose's enough to connect from two min by y
        while(i<shell.size()) {
            left_idx = start_left_idx;
            start_right_idx = i;
            right_idx = start_right_idx;
            current_x_plane = shell[start_right_idx].x;

            triangulation.push_back(Edge(shell[start_left_idx], shell[start_right_idx]));

            while (left_idx != start_right_idx && shell[right_idx].x == current_x_plane) {
                float c = Distance(shell[left_idx], shell[right_idx + 1]);
                float b = Distance(shell[right_idx], shell[right_idx+1]);
                float a = Distance(shell[left_idx], shell[right_idx]);
                float angle_on_c = std::acos((a*a + b*b - c*c)/(2*a*b));
                float angle_on_a = std::acos((c*c+b*b-a*a)/(2*b*c));
                float angle_on_b = M_PI - angle_on_a - angle_on_c;
                float xxx = b+c;



                float c2 = Distance(shell[left_idx + 1], shell[right_idx]);
                float b2 = Distance(shell[left_idx], shell[left_idx+1]);
                float a2 = Distance(shell[left_idx], shell[right_idx]);
                float angle_on_c_2 = std::acos((a2*a2 + b2*b2 - c2*c2)/(2*a2*b2));
                float angle_on_a_2 = std::acos((b2*b2+c2*c2-a2*a2)/(2*b2*c2));
                float angle_on_b_2 = M_PI - angle_on_c_2 - angle_on_a_2;

                float yyy =c2 + b2;

                Point c_center = Point((shell[left_idx].x+shell[right_idx].x)/2, (shell[left_idx].y+shell[right_idx].y)/2, (shell[left_idx].z+shell[right_idx].z)/2);


                if (std::max({angle_on_a, angle_on_b, angle_on_c}) > M_PI*0.5 && std::max({angle_on_a_2, angle_on_b_2, angle_on_c_2}) <= M_PI*0.5){
                    //not suits Delone property
                    triangulation.push_back(Edge(shell[right_idx], shell[right_idx+1]));
                    triangulation.push_back(Edge(shell[left_idx], shell[++right_idx]));
                    continue;
                }
                if (std::max({angle_on_a, angle_on_b, angle_on_c}) <= M_PI*0.5 &&  std::max({angle_on_a_2, angle_on_b_2, angle_on_c_2})>M_PI*0.5){
                    //not suits Delone property
                    triangulation.push_back(Edge(shell[++left_idx], shell[right_idx]));
                    continue;
                }

                if (Distance(c_center, shell[left_idx+1])< Distance(c_center, shell[right_idx+1])){
                    triangulation.push_back(Edge(shell[++left_idx], shell[right_idx]));
                }
                else{
                    triangulation.push_back(Edge(shell[right_idx], shell[right_idx+1]));
                    triangulation.push_back(Edge(shell[left_idx], shell[++right_idx]));
                }
            }
            while (left_idx != start_right_idx) {
                triangulation.push_back(Edge(shell[++left_idx], shell[right_idx-1]));
            }
            while (shell[right_idx].x == current_x_plane && right_idx != shell.size() - 1) {
                triangulation.push_back(Edge(shell[right_idx], shell[right_idx+1]));
                triangulation.push_back(Edge(shell[left_idx-1], shell[++right_idx]));
            }
            start_left_idx = start_right_idx;
            i = (shell[right_idx].x != current_x_plane) ? right_idx : ++right_idx;
        }

        std::fstream file;
        file.open("triangle.txt");
        for (int i=0;i<triangulation.size(); ++i){
            file<<triangulation[i].from.x<<triangulation[i].from.y<<triangulation[i].from.z<<"\n\r";
            file<<triangulation[i].to.x<<triangulation[i].to.y<<triangulation[i].to.z<<"\n\r";
            std::cout << triangulation[i].from.x<<", "<<triangulation[i].from.y<<", "<<triangulation[i].from.z<<", "<<triangulation[i].to.x<<", "<<triangulation[i].to.y<<", "<<triangulation[i].to.z<<",\n\r";
        }
    }

private:
    std::vector<Point> cloud;
    std::set<Point, PointsComp> cloud_copy;
    std::vector<Point> shell;
    std::vector<Edge> triangulation;
    Point center;
};

int main() {
    CloudTriangulation ttt = CloudTriangulation("shell.txt");
    ttt.BuildTriangulation();
}
