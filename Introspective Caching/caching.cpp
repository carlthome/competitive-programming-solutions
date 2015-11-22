#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct object {
	int id, last_position;
	object(){}
  object(int _id, int _last_position) : id(_id), last_position(_last_position) { }
	
	bool operator < (struct object X) const{
		return last_position < X.last_position;
	}
};

int main(){
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  
	int cache_size, objects_count, accesses_count;
	while(cin >> cache_size >> objects_count >> accesses_count) {
    int cachings = 0;
  
    vector<int> accesses (accesses_count);
		for(int access = 0; access < accesses_count; access++)
      cin >> accesses[access];
		
    vector<int> last (objects_count, accesses_count);
    vector<int> priority (accesses_count);
		for(int access = accesses_count-1; access >= 0; access--) {
      const auto& object_id = accesses[access];
			priority[access] = last[object_id];
			last[object_id] = access;
		}
		
		priority_queue<object> cache;
    vector<bool> cached (objects_count, false);
		for(int access = 0; access < accesses_count; access++) {
			const auto& object_id = accesses[access];
			
			if(!cached[object_id]) {
				cached[object_id] = true;
				++cachings;

				if(cachings > cache_size) {
          const auto& object_to_remove = cache.top();
					cached[object_to_remove.id] = false;
					cache.pop();
				}
			}
			
			cache.push(object(object_id, priority[access]));
		}

    cout << cachings << endl;
	}
	
	return 0;
}
