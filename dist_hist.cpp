#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

// distance quantization
double max_dist = 10.0;
int bin_size_dist = 1000;

int sample_size = 2500;

int main(int argc, char **argv) {
    cout << argv[1] << endl;
    
    fstream fp;

	vector<int> vmale(sample_size), vfemale(sample_size);
	fp.open(argv[1], fstream::in);
	for(int i=0; i < sample_size; i++)
		fp >> vmale[i];
	for(int i=0; i < sample_size; i++)
		fp >> vfemale[i];
	fp.close();

	map<int,int> all, male, female;
    for(int x: vmale) {
        all[x] += 1;
        male[x] += 1;
    }
    for(int x: vfemale) {
        all[x] += 1;
        female[x] += 1;
    }
	//copy(vmale.begin(), vmale.end(), inserter(all, all.end()));
	//copy(vmale.begin(), vmale.end(), inserter(male, male.end()));
	//copy(vfemale.begin(), vfemale.end(), inserter(all, all.end()));
	//copy(vfemale.begin(), vfemale.end(), inserter(female, female.end()));

	string scores_path = "../matrices/";
	string arr[] = {"gaitgl", "gaitpart", "gaitset"};
	vector<string> alg(arr, arr+3);
	for(int i=0; i < alg.size(); i++) {
		vector<int> genM(bin_size_dist+1, 0), impM(bin_size_dist+1, 0), genF(bin_size_dist+1, 0), impF(bin_size_dist+1, 0), impC(bin_size_dist+1, 0);

		string full_path = scores_path+alg[i]+"/";

		// get all files in full_path
		vector<string> files;
		DIR *dir;
		struct dirent *ent;
		dir = opendir(full_path.c_str());
		assert(dir != NULL);
		while((ent = readdir (dir)) != NULL)
			files.push_back(ent->d_name);
		closedir(dir);
		sort(files.begin(), files.end());

		// parse files
		string prefix = "gallery";
		for(int j=0; j < files.size(); j++) {
			if(files[j].compare(0, prefix.size(), prefix) != 0)
				continue;

			fp.open((full_path+files[j]).c_str(), fstream::in);

			// parse header
			string str;
			getline(fp, str);
			vector<int> indices;
			vector<bool> is_col_male;
			vector<int> col_id;
            vector<int> col_count;
			stringstream ss(str);
			int k=0;
			while(ss.good()) {
				string substr;
				getline(ss, substr, ',');
				if(substr != "") {
					int id = atoi(substr.c_str());
					if(all.find(id) != all.end()) {
						indices.push_back(k);
						is_col_male.push_back(male.find(id) != male.end());
						col_id.push_back(id);
                        col_count.push_back(all[id]);
					}
				}
				k++;
			}

			// parse rows
			int rows=0;
			for(;;) {
				getline(fp, str);
				if(str.size() == 0)
					break;

				stringstream ss(str);
				int k=0, id, count, next, next_idx;
				bool is_male;
				while(ss.good()) {
					string substr;
					getline(ss, substr, ',');
					if(substr != "") {
						if(k == 0) {
							if(all.find(atoi(substr.c_str())) != all.end()) {
								id = atoi(substr.c_str());
                                count = all[id];
								is_male = male.find(id) != male.end();
								rows++;
                                
                                next_idx=0;
                                next=indices[next_idx];
							}
							else
								break;
						}
						else if(k == next) {
                            int id2 = col_id[next_idx];
                            bool is_male2 = is_col_male[next_idx];
                            int count2 = col_count[next_idx];
							double dist = atof(substr.c_str());
							int norm_dist = (int)((min(dist, max_dist)/max_dist)*bin_size_dist);
							if(id2 == id) {
								if(is_male)
									genM[norm_dist] += count;
								else
									genF[norm_dist] += count;
							}
							else if(is_male and is_male2) {
								impM[norm_dist] += count*count2;
							}
							else if(not is_male and not is_male2) {
								impF[norm_dist] += count*count2;
							}
							else {
								impC[norm_dist] += count*count2;
							}
                            
                            next_idx++;
                            if(next_idx < indices.size())
                                next=indices[next_idx];
                            else
                                break;
						}
					}
					k++;
			    }
			}

			fp.close();
		}

		string output_file = argv[2];
		output_file += "_"+alg[i]+".txt";
		fp.open(output_file.c_str(), fstream::out);
		fp << genM[0];
		for(int j=1; j <= bin_size_dist; j++)
			fp << " " << genM[j];
		fp << endl;
		fp << genF[0];
		for(int j=1; j <= bin_size_dist; j++)
			fp << " " << genF[j];
		fp << endl;
		fp << impM[0];
		for(int j=1; j <= bin_size_dist; j++)
			fp << " " << impM[j];
		fp << endl;
		fp << impF[0];
		for(int j=1; j <= bin_size_dist; j++)
			fp << " " << impF[j];
		fp << endl;
		fp << impC[0];
		for(int j=1; j <= bin_size_dist; j++)
			fp << " " << impC[j];
		fp << endl;
		fp.close();
	}

	cout << "done" << endl;
    
	return 0;
}
