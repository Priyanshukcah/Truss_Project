#include<iostream>
#include<vector>
using namespace std;

class Joint {
public:
    int id;
    double x, y;
    int hasUnknownX; // 1 if unknown reaction in X, 0 if not
    int hasUnknownY; // 1 if unknown reaction in Y, 0 if not
    double loadX;    // Force in X direction
    double loadY;    // Force in Y direction

    Joint() {        // this is for bydefault values
        id = 0;
        x = 0;
        y = 0;
        hasUnknownX = 0;
        hasUnknownY = 0;
        loadX = 0;
        loadY = 0;
    }
};
class Member {       //actually this is roadd
public:
    int id;
    int point1;
    int point2;
};

// Class to store Special Point, inputs these are spacial
class SpecialPoint {
public:
    int jointId;
    int type; // 1 for X-direction, 2 for Y-direction
};

// Class to store Load inputs
class LoadForce {
public:
    int jointId;
    double fx;
    double fy;
};

int main() {
    int numJoints, numMembers, numSpecialPts, numLoads;

    cin >> numJoints >> numMembers >> numSpecialPts >> numLoads;     // Line 1: Read the counts

    // Create simple lists (vectors) to store the data
    vector<Joint> joints(numJoints + 1); // +1 so we can use 1-based index directly (joint 1 at index 1)
    vector<Member> members(numMembers);
    vector<SpecialPoint> specialPoints(numSpecialPts);
    vector<LoadForce> loadForces(numLoads);

    // 1. Read all Joints
    for (int i = 0; i < numJoints; i++) {
        int id;
        double x, y;
        cin >> id >> x >> y;

        joints[id].id = id;
        joints[id].x = x;
        joints[id].y = y;
    }

    // 2. Read all Members
    for (int i = 0; i < numMembers; i++) {
        cin >> members[i].id >> members[i].point1 >> members[i].point2;
    }

    // 3. Read Special Points (Supports)
    for (int i = 0; i < numSpecialPts; i++) {
        cin >> specialPoints[i].jointId >> specialPoints[i].type;

        int jId = specialPoints[i].jointId;
        if (specialPoints[i].type == 1) {
            joints[jId].hasUnknownX = 1;
        } else if (specialPoints[i].type == 2) {
            joints[jId].hasUnknownY = 1;
        }
    }

    // 4. Read Load Forces and assignig them
    for (int i = 0; i < numLoads; i++) {
        cin >> loadForces[i].jointId >> loadForces[i].fx >> loadForces[i].fy;

        int jId = loadForces[i].jointId;
        joints[jId].loadX = loadForces[i].fx;
        joints[jId].loadY = loadForces[i].fy;
    }

   
    //this is optional if we want to use the data then we just have to use i mean there no nead for output of this
    cout << "\n--- STORED JOINTS ---\n";
    for (int i = 1; i <= numJoints; i++) {
        cout << "Joint " << joints[i].id 
             << " -> Coordinates: (" << joints[i].x << ", " << joints[i].y << ")"
             << " | Unknown X: " << joints[i].hasUnknownX 
             << " | Unknown Y: " << joints[i].hasUnknownY
             << " | Load: (" << joints[i].loadX << ", " << joints[i].loadY << ")\n";
    }

    cout << "\n--- STORED MEMBERS ---\n";
    for (int i = 0; i < numMembers; i++) {
        cout << "Member " << members[i].id 
             << " connects Joint " << members[i].point1 
             << " to Joint " << members[i].point2 << "\n";
    }

    return 0;
}