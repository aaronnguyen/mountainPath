#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

   int keyAmount;
   cin >> keyAmount;

   char charKey;
   int keyVal;
   unordered_map<char, int> charValMap;

   for (int i = 0; i < keyAmount; i++){
       cin >> charKey >> keyVal;
       charValMap[charKey] = keyVal;
   }

   int row, col;
   cin >> row >> col;

   vector<vector<char>> terrainMap(row, vector<char>(col, '0'));
   char inCharVal;
   for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cin >> inCharVal;
            terrainMap[i][j] = inCharVal;
        }
   }

   int startX, startY, endX, endY;
   cin >> startX >> startY;
   cin >> endX >> endY;

   cout << "Start: (" << startX << "," << startY << ")\n";
   cout << "End: (" << endX << "," << endY << ")\n";

   cout << "TerrainMap: \n";
   for(auto i: terrainMap){
       for(auto cell: i){
           cout << cell << " ";
       }
       cout << "\n";
   }

   return 0;
}
