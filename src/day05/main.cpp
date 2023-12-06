#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include"ReadFile.h"
#include"StrUtils.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

void readInput(vector<string> &ll)
{
	ReadFile inf("input.txt");
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ll.push_back(ss);
	}
	inf.close();
}

#define ullong unsigned long long

class Range
{
public:
	Range(ullong s, ullong d, ullong l) : srcStart(s), desStart(d), len(l) {}
	bool inRange(ullong in)
	{
		if(in < srcStart) return false;
		if(in > srcStart + len) return false;
		return true;
	}

	ullong getValue(ullong in)
	{
		if(!inRange(in)) { cout << "ERROR" << endl; exit(0); }
		ullong ll = in - srcStart;
		return desStart + ll;
	}

private:
	ullong srcStart;
	ullong desStart;
	ullong len;
};

vector<ullong> seeds;
vector<Range> seed2soil;
vector<Range> soil2fert;
vector<Range> fert2h2o;
vector<Range> h2o2light;
vector<Range> light2temp;
vector<Range> temp2hum;
vector<Range> hum2loc;

void parseInput(const vector<string> &ll)
{
	vector<Range> *curVec = nullptr;
	for(string s : ll)
	{
		if(StrUtils::startsWith(s, "seeds: "))
		{
			std::vector<std::string> sds;
			StrUtils::tokenize(s.substr(6), " ", sds);
			for(string sd : sds)
				seeds.push_back(std::stoll(sd));
		}
		else if(s == "seed-to-soil map:")			curVec = &seed2soil;
		else if(s == "soil-to-fertilizer map:")		curVec = &soil2fert;
		else if(s == "fertilizer-to-water map:")	curVec = &fert2h2o;
		else if(s == "water-to-light map:")			curVec = &h2o2light;
		else if(s == "light-to-temperature map:")	curVec = &light2temp;
		else if(s == "temperature-to-humidity map:")curVec = &temp2hum;
		else if(s == "humidity-to-location map:")	curVec = &hum2loc;
		else if(curVec != nullptr)
		{
			std::vector<std::string> vals;
			StrUtils::tokenize(s, " ", vals);
			if(vals.size() == 3)
			{
				ullong dstart = std::stoll(vals[0]);
				ullong sstart = std::stoll(vals[1]);
				ullong len = std::stoll(vals[2]);
				curVec->emplace_back(sstart, dstart, len);
			}
		}
		else
			std::cerr << "ERROR parsing input" << endl;
	}
}

int main()
{
	vector<string> ll;
	readInput(ll);
	parseInput(ll);

	ullong answer1 = ULLONG_MAX;

	for(ullong seed : seeds)
	{
		ullong soil = seed;
		for(Range r : seed2soil)
			if(r.inRange(soil)) { soil = r.getValue(soil); break; }

		ullong fert = soil;
		for(Range r : soil2fert)
			if(r.inRange(fert)) { fert = r.getValue(fert); break; }

		ullong h2o = fert;
		for(Range r : fert2h2o)
			if(r.inRange(h2o)) { h2o = r.getValue(h2o); break; }

		ullong light = h2o;
		for(Range r : h2o2light)
			if(r.inRange(light)) { light = r.getValue(light); break; }

		ullong temp = light;
		for(Range r : light2temp)
			if(r.inRange(temp)) { temp = r.getValue(temp); break; }

		ullong hum = temp;
		for(Range r : temp2hum)
			if(r.inRange(hum)) { hum = r.getValue(hum); break; }

		ullong loc = hum;
		for(Range r : hum2loc)
			if(r.inRange(loc)) { loc = r.getValue(loc); break; }

		answer1 = std::min(answer1, loc);
	}

	cout << "PART1 answer = " << answer1 << endl;

	////////////////////////////////////////

	ullong answer2 = ULLONG_MAX;
	for(int i = 0; i < seeds.size(); i += 2)
	{
		ullong seed = seeds[i];
		ullong len = seeds[i+1];

		for(ullong j = 0; j < len; j++)
		{
			ullong soil = seed;
			for(Range r : seed2soil)
				if(r.inRange(soil)) { soil = r.getValue(soil); break; }

			ullong fert = soil;
			for(Range r : soil2fert)
				if(r.inRange(fert)) { fert = r.getValue(fert); break; }

			ullong h2o = fert;
			for(Range r : fert2h2o)
				if(r.inRange(h2o)) { h2o = r.getValue(h2o); break; }

			ullong light = h2o;
			for(Range r : h2o2light)
				if(r.inRange(light)) { light = r.getValue(light); break; }

			ullong temp = light;
			for(Range r : light2temp)
				if(r.inRange(temp)) { temp = r.getValue(temp); break; }

			ullong hum = temp;
			for(Range r : temp2hum)
				if(r.inRange(hum)) { hum = r.getValue(hum); break; }

			ullong loc = hum;
			for(Range r : hum2loc)
				if(r.inRange(loc)) { loc = r.getValue(loc); break; }

			answer2 = std::min(answer2, loc);
			seed++;
		}
	}

	cout << "PART2 answer = " << answer2 << endl;

	return 0;
}
