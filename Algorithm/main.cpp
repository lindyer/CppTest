//http://www.cnblogs.com/maybe2030/
//http://www.cnblogs.com/maybe2030/category/697575.html

#include <iostream>
#include <cstdlib>     // Need random(), srandom()
#include <ctime>      // Need time()
#include <vector>       // Need vector
#include <algorithm>    // Need for_each()
#include <numeric>      // Need accumulate()
#include <functional>   // Need multiplies() (or times())
#include <time.h>
using namespace std;

void printArray(vector<int>& nums){
    for(int i = 0;i < nums.size(); ++i){
        cout << nums[i] << " ";
    }
    cout << endl;
}

//产生随机数，count为产生的个数，range为产生的范围
vector<int> randomVector(int count,int range = 65535){
    vector<int> nums;
    srand((unsigned)time(0));  //以当前时间戳初始化随机器
    for(int i = 0;i < count; ++i){
        nums.push_back((rand()%range));
    }
    return nums;
}

//插值查找
//   在介绍插值查找之前，首先考虑一个新问题，为什么上述算法一定要是折半，而不是折四分之一或者折更多呢？
//　　打个比方，在英文字典里面查“apple”，你下意识翻开字典是翻前面的书页还是后面的书页呢？如果再让你查“zoo”，你又怎么查？很显然，这里你绝对不会是从中间开始查起，而是有一定目的的往前或往后翻。
//　　同样的，比如要在取值范围1 ~ 10000 之间 100 个元素从小到大均匀分布的数组中查找5， 我们自然会考虑从数组下标较小的开始查找。
//　　经过以上分析，折半查找这种查找方式，不是自适应的（也就是说是傻瓜式的）。二分查找中查找点计算如下：
//　　mid=(low+high)/2, 即mid=low+1/2*(high-low);
//　　通过类比，我们可以将查找的点改进为如下：
//　　mid=low+(key-a[low])/(a[high]-a[low])*(high-low)，
//　　也就是将上述的比例参数1/2改进为自适应的，根据关键字在整个有序表中所处的位置，让mid值的变化更靠近关键字key，这样也就间接地减少了比较次数。
//　　基本思想：基于二分查找算法，将查找点的选择改进为自适应选择，可以提高查找效率。当然，差值查找也属于有序查找。
//　　注：对于表长较大，而关键字分布又比较均匀的查找表来说，插值查找算法的平均性能比折半查找要好的多。反之，数组中如果分布非常不均匀，那么插值查找未必是很合适的选择。
//　　复杂度分析：查找成功或者失败的时间复杂度均为O(log2(log2n))。
int insertionSearch(vector<int> nums,int value,int low,int high){
    int mid = low + (value - nums[low]) * (high - low)/(nums[high] - nums[low]);
    cout <<low  << " "<< high << " " << mid << endl;
    if((mid <= low && nums[mid] != nums[low]) || ( mid >= high && nums[mid] != nums[high])){  //exception
        return -1;
    }
    if(nums[mid] == value){
        return mid;
    }
    if(nums[mid] > value){
        return insertionSearch(nums,value,low,mid - 1);
    }
    if(nums[mid] < value){
        return insertionSearch(nums,value,mid + 1,high);
    }
}

//二分查找
//说明：元素必须是有序的，如果是无序的则要先进行排序操作。
//基本思想：也称为是折半查找，属于有序查找算法。用给定值k先与中间结点的关键字比较，中间结点把线形表分成两个子表，若相等则查找成功；若不相等，再根据k与该中间结点关键字的比较结果确定下一步查找哪个子表，这样递归进行，直到查找到或查找结束发现表中没有这样的结点。
//复杂度分析：最坏情况下，关键词比较次数为log2(n+1)，且期望时间复杂度为O(log2n)；
//注：折半查找的前提条件是需要有序表顺序存储，对于静态查找表，一次排序后不再变化，折半查找能得到不错的效率。但对于需要频繁执行插入或删除操作的数据集来说，维护有序的排序会带来不小的工作量，那就不建议使用。——《大话数据结构》
int binarySearch(vector<int> nums,int value){
    int low = 0,high = nums.size() - 1,mid;
    while(low <= high){
        mid = (low + high) / 2;
        if(nums[mid] == value){
            return mid;
        }
        if(nums[mid] > value){
            high = mid - 1;
        }
        if(nums[mid] < value){
            low = mid + 1;
        }
    }
    return -1;
}
//二分查找，递归版本
int binarySearch2(vector<int> nums,int value,int low,int high){
    int mid = low + (high -  low)/2;
    if((mid <= low && nums[mid] != nums[low]) || ( mid >= high && nums[mid] != nums[high])){  //exception
        return -1;
    }
    if(nums[mid] == value){
        return mid;
    }
    if(nums[mid] > value){
        return binarySearch2(nums,value,low,mid - 1);
    }
    if(nums[mid] < value){
        return binarySearch2(nums,value,mid + 1,high);
    }
}

//顺序查找
//说明：顺序查找适合于存储结构为顺序存储或链接存储的线性表。
//基本思想：
//    顺序查找也称为线形查找，属于无序查找算法。从数据结构线形表的一端开始，顺序扫描，依次将扫描到的结点关键字与给定值k相比较，若相等则表示查找成功；若扫描结束仍没有找到关键字等于k的结点，表示查找失败。
//复杂度分析：
//    查找成功时的平均查找长度为：（假设每个数据元素的概率相等） ASL = 1/n(1+2+3+…+n) = (n+1)/2 ;
//    当查找不成功时，需要n+1次比较，时间复杂度为O(n);
//    所以，顺序查找的时间复杂度为O(n)。
int sequenceSearch(vector<int> nums,int value){
    for(int i = 0;i < nums.size(); ++i){
        if(nums.at(i) == value){
            return i;
        }
    }
    return -1;
}
void shellSort(vector<int> &nums);
int main(){
//    vector<int> arr;
//    arr.assign(10,0);
//    printArray(arr);
    vector<int> nums = randomVector(10,10);
//    shellSort(nums);
    printArray(nums);
//    cout << sequenceSearch(nums,5);
//    cout << binarySearch2(nums,5,0,nums.size() - 1);
//    cout << insertionSearch(nums,5000,0,nums.size() - 1);

}

//希尔排序
void shellSort(vector<int> &nums){
    for(int gap = nums.size() >> 1; gap > 0; gap >>= 1){ //times
        for(int i = gap; i < nums.size(); i++){ //position
            int temp = nums[i];
            int  j = i- gap;
            for(; j >= 0 && nums[j] > temp; j -= gap){
                nums[j + gap] = nums[j];
            }
            nums[j + gap] = temp;
        }
    }
}
int main4(){
    long time1 = time(0);
    vector<int> nums = randomVector(10000000,100000);
//    printArray(nums);
    shellSort(nums);
//    printArray(nums);
    long time2 = time(0);
    cout << time2 << " " << time1 << " " << (time2 - time1) << endl;
}



//选择排序
//    选择排序的原理是，每次都从乱序数组中找到最大（最小）值，放到当前乱序数组头部，最终使数组有序。
//步骤
//    从左开始，选择后面元素中最小值，和最左元素交换
//    从当前已交换位置往后执行，直到最后一个元素
//复杂度分析
//    每次要找一遍最小值，最坏情况下找n次，这样的过程要执行n次，所以时间复杂度还是O(n^2)。空间复杂度是O(n)。
void selectionSort(vector<int> &nums){
    for(int i = 0;i < nums.size(); ++i){  //position
        int min = i;
        for(int j = i + 1;j < nums.size(); ++j){
            if(nums[j] < nums[min]){
                min = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[min];
        nums[min] = temp;
    }
}
int main3(){
    vector<int> nums = {5,2,1,4,3};
    selectionSort(nums);
    printArray(nums);
}

//插入排序
//    插入排序的原理是从左到右，把选出的一个数和前面的数进行比较，找到最适合它的位置放入，使前面部分有序。
//步骤
//    从左开始，选出当前位置的数x，和它之前的数y比较，如果x < y则交换两者
//    对x之前的数都执行1步骤，直到前面的数字都有序
//    选择有序部分后一个数字，插入到前面有序部分，直到没有数字可选择
//复杂度分析
//    因为要选择n次，而且插入时最坏要比较n次，所以时间复杂度同样是O(n^2)。空间复杂度是O(n)。
void insertSort(vector<int> &nums){
    for(int i = 1;i < nums.size(); ++i){ //position
        for(int j = i;j > 0; --j){
            if(nums[j] < nums[j-1]){
                int temp = nums[j];
                nums[j] = nums[j -1];
                nums[j - 1] = temp;
            }
        }
    }
}
int main2(){
    vector<int> nums = {2,1,8,5};
    insertSort(nums);
    printArray(nums);
}



//冒泡排序
//    冒泡排序是最简单粗暴的排序方法之一。它的原理很简单，每次从左到右两两比较，把大的交换到后面，每次可以确保将前M个元素的最大值移动到最右边。
//步骤
//    从左开始比较相邻的两个元素x和y，如果 x > y 就交换两者
//    执行比较和交换，直到到达数组的最后一个元素
//    重复执行1和2，直到执行n次，也就是n个最大元素都排到了最后
//复杂度分析
//    由于我们要重复执行n次冒泡，每次冒泡要执行n次比较（实际是1到n的等差数列，也就是(a1 + an) * n / 2），也就是 O(n^2)。 空间复杂度是O(n)。
void bubbleSort(vector<int> &nums){
    for(int i = 0;i < nums.size() - 1; ++i){ //times
        for(int j = 0; j < nums.size() - i -1; ++j){ //position
            if(nums[j] > nums[j+1]){
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}
int main1(){
    vector<int> vect = {1,8,6,4};
    bubbleSort(vect);
    printArray(vect);
}


//template<class _Ty>
//struct multiplies : binary_function<_Ty, _Ty, _Ty> {

//    _Ty operator()(const _Ty& _X, const _Ty& _Y) const

//    {return (_X * _Y); }

//};
/*
#define MAX 10
vector<long> v(MAX);    // Vector object

int main()
{
  // Fill vector using conventional loop
  //
  for (int i = 0; i < MAX; i++)
    v[i] = i + 1;

  // Accumulate the sum of contained values
  //
  long sum =
    accumulate(v.begin(), v.end(), 0);
  cout << "Sum of values == " << sum << endl;

  // Accumulate the product of contained values
  //
  long product =
    accumulate(v.begin(), v.end(), 1, multiplies<long>());//注意这行
  cout << "Product of values == " << product << endl;

  return 0;
}
*/

/*
#define VSIZE 24        // Size of vector
vector<long> v(VSIZE);  // Vector object

// Function prototypes
void initialize(long &ri);
void show(const long &ri);
bool isMinus(const long &ri);  // Predicate function

int main()
{
  srand( time(NULL) );  // Seed random generator

  for_each(v.begin(), v.end(), initialize);//调用普通函数
  cout << "Vector of signed long integers" << endl;
  for_each(v.begin(), v.end(), show);
  cout << endl;

  // Use predicate function to count negative values
  //
  int count = 0;
  vector<long>::iterator p;
  p = find_if(v.begin(), v.end(), isMinus);//调用断言函数
  while (p != v.end()) {
    count++;
    p = find_if(p + 1, v.end(), isMinus);
  }
  cout << "Number of values: " << VSIZE << endl;
  cout << "Negative values : " << count << endl;

  return 0;
}

// Set ri to a signed integer value
void initialize(long &ri)
{
  ri = ( rand() - (RAND_MAX / 2) );
  //  ri = random();
}

// Display value of ri
void show(const long &ri)
{
  cout << ri << "  ";
}

// Returns true if ri is less than 0
bool isMinus(const long &ri)
{
  return (ri < 0);
}
*/

/*
#include <iostream>
#include <cstdlib>    // Need random(), srandom()
#include <ctime>      // Need time()
#include <algorithm>   // Need sort(), copy()
#include <vector>      // Need vector
#include <iterator>
using namespace std;

void Display(vector<int>& v, const char* s);

int main()
{
  // Seed the random number generator
  srand( time(NULL) );

  // Construct vector and fill with random integer values
  vector<int> collection(10);
  for (int i = 0; i < 10; i++)
    collection[i] = rand() % 10000;

  // Display, sort, and redisplay
  Display(collection, "Before sorting");
  sort(collection.begin(), collection.end());
  Display(collection, "After sorting");
  return 0;
}

// Display label s and contents of integer vector v
void Display(vector<int>& v, const char* s)
{
  cout << endl << s << endl;
  copy(v.begin(), v.end(),
    ostream_iterator<int>(cout, "\t"));
  cout << endl;
}
*/





//#include <iostream>
//#include <algorithm>
//using namespace std;
//#include <vector>
//vector<int> intVector(100);
//int main()
//{
//    intVector[20] = 50;
////    vector<int>::iterator intIter =
////      find(intVector.begin(), intVector.end(), 50);
////    if (intIter != intVector.end())
////      cout << "Vector contains value " << *intIter << endl;
////    else
////      cout << "Vector does not contain 50" << endl;
////    cout << "Vector contains value " << *intIter << endl;

//    system("pause");
//    return 0;
//}

