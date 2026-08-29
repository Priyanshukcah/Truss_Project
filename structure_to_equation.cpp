#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

class Joint
{
public:
    double x, y;
    bool restrainX, restrainY;
    double loadX, loadY;

    Joint(double x_, double y_, bool rx = false, bool ry = false,double lx = 0, double ly = 0)
        : x(x_), y(y_), restrainX(rx), restrainY(ry), loadX(lx), loadY(ly)
    {
    }
};

class Member
{
public:
    int j1, j2;
    Member(int a, int b) : j1(a), j2(b) {}
};

class TrussSystem
{
private:
    vector<Joint> joints;
    vector<Member> members;
    vector<vector<double>> A;
    vector<double> b;
    int numUnknowns = 0;

public:
    void addJoint(const Joint& j)
    {
        joints.push_back(j);
    }
    void addMember(int j1, int j2)
    {
        members.push_back(Member(j1, j2));
    }

    void buildEquations()
    {
        int nJoints = joints.size();

        vector<pair<char, int>> unknowns;
        for (int m = 0; m < (int)members.size(); m++)
            unknowns.push_back({'M', m});
        for (int jt = 0; jt < nJoints; jt++)
        {
            if (joints[jt].restrainX) unknowns.push_back({'X', jt});
            if (joints[jt].restrainY) unknowns.push_back({'Y', jt});
        }
        numUnknowns = unknowns.size();

        A.assign(2 * nJoints, vector<double>(numUnknowns, 0.0));
        b.assign(2 * nJoints, 0.0);

        for (int m = 0; m < (int)members.size(); m++)
        {
            int a = members[m].j1, c = members[m].j2;
            double dx = joints[c].x - joints[a].x;
            double dy = joints[c].y - joints[a].y;
            double L = sqrt(dx * dx + dy * dy);
            double cosT = dx / L, sinT = dy / L;

            A[2 * a][m]     += cosT;
            A[2 * a + 1][m] += sinT;
            A[2 * c][m]     += -cosT;
            A[2 * c + 1][m] += -sinT;
        }

        for (int u = 0; u < numUnknowns; u++)
        {
            if (unknowns[u].first == 'X')
                A[2 * unknowns[u].second][u] = 1.0;
            else if (unknowns[u].first == 'Y')
                A[2 * unknowns[u].second + 1][u] = 1.0;
        }

        for (int jt = 0; jt < nJoints; jt++)
        {
            b[2 * jt]     = -joints[jt].loadX;
            b[2 * jt + 1] = -joints[jt].loadY;
        }
    }

    void printSystem() const
    {
        cout << "Coefficient matrix A (" << A.size() << " x " << numUnknowns << "):\n";
        for (auto& row : A)
        {
            for (double v : row) printf("%7.3f ", v);
            cout << "\n";
        }
        cout << "\nRHS vector b:\n";
        for (double v : b) printf("%7.3f\n", v);
    }
};

int main()
{
    TrussSystem truss;

    truss.addJoint(Joint(0, 0, true, true));
    truss.addJoint(Joint(4, 0, false, true));
    truss.addJoint(Joint(2, 3, false, false, 0, -10));

    truss.addMember(0, 1);
    truss.addMember(0, 2);
    truss.addMember(1, 2);

    truss.buildEquations();
    truss.printSystem();

    return 0;
}