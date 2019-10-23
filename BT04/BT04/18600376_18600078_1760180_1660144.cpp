//#include <stdafx.h>
#include <tchar.h>
#include <iostream>

using namespace std;

struct NODE {
	int Key;
	NODE* pNext;
};


NODE* CreateNode(int Data)
{
	NODE* pNode;
	pNode = new NODE; //Xin cấp phát bộ nhớ động để tạo một phần tử (node) mới
	if (pNode == NULL)
		return NULL;
	pNode->Key = Data;
	pNode->pNext = NULL;
	return pNode;
}

void PrintList(NODE* pHead)
{
	NODE* pNode;
	pNode = pHead;
	while (pNode != NULL)
	{
		cout << pNode->Key << " " ;
		pNode = pNode->pNext; //Ghi chu: thao tác này dùng để làm gì? --> Đưa con trỏ trỏ tới vị trí node tiếp theo
	}
}
void RemoveAll(NODE*& pHead) //Ghi chu: Ý nghĩa của ký hiệu & -->Lấy địa chỉ của node ngay khi truyền vào hàm
{
	NODE* pNode;
	while (pHead != NULL)
	{
		pNode = pHead;
		pHead = pHead->pNext;
		delete pNode;
	}
	pHead = NULL; //Ghi chu: Tại sao phải thực hiện phép gán này --> Sau khi xóa hết các node trong danh sach
	//liên kết, cần phải gắn pHead = NULL để hiểu rằng con trỏ không trỏ tới bất kỳ một vị trí ô nhớ nào cả.
}

/* Áp dụng - Nâng cao */
/* 1. Hàm tính tổng giá trị các phần tử trên danh sách liên kết đơn */
int SumList(NODE* pHead)
{
	int s = 0;
	NODE* pNode = pHead;
	while (pNode != NULL)
	{
		s += pNode->Key;
		pNode = pNode->pNext;
	}
	return s;
}


/* 2. Hàm tìm giá trị nguyên lớn nhất */

int MaxList(NODE* pHead)
{
	NODE* pNode = pHead;
	int max = pHead->Key;
	while (pNode != NULL)
	{
		int temp = pNode->Key;
		if (temp > max)
			max = temp;
		pNode = pNode->pNext;
	}
	return max;
}
/* 3. Hàm đếm số lượng các phần tử của danh sách liên kết đơn */
int CountList(NODE* pHead)
{
	int dem = 0;
	NODE* pNode = pHead;
	while (pNode != NULL)
	{
		pNode = pNode->pNext;
		dem++;
	}
	return dem;
}

/* 5. Chương trình mẫu cho phép xóa phần tử đầu danh sách liên kết đơn. */
void XoaDau(NODE*& pHead)
{
	NODE* pNode = pHead;
	if (pHead == NULL)
		return;
	pHead = pHead->pNext;
	delete pNode;
}

/* 6. Chương trình xóa phần tử cuối danh sách liên kết đơn */
void XoaCuoi(NODE*& pHead)
{
	if (pHead == NULL)
		return;
	if (pHead->pNext == NULL)
	{
		delete pHead;
		pHead = NULL;
		return;
	}

	NODE* pNode = pHead;
	while (pNode->pNext->pNext != NULL)
		pNode = pNode->pNext;

	delete pNode->pNext;
	pNode->pNext = NULL;
}

/* 7. Chương trình cho biết số lượng các phần tử
trên danh sách liên kết đơn có giá trị trùng với giá trị x được cho trước.*/
int DemX(NODE* pHead, int x)
{
	int dem = 0;
	NODE* pNode = pHead;
	while (pNode != NULL)
	{
		if (pNode->Key == x)
			dem++;
		pNode = pNode->pNext;
	}
	return dem;
}

/* 8.Bổ sung chương trình mẫu cho phép tạo một danh sách liên kết đơn gồm các phần tử mang giá trị
nguyên trong đó không có cặp phần tử nào mang giá trị giống nhau. 
	--> Đã Update hàm AddHead và AddTail không cho nhập các giá trị đã có trong danh sách liên k
*/

bool AddHead(NODE*& pHead, int Data)
{
	NODE* pNode;
	pNode = CreateNode(Data);
	if (pNode == NULL)
		return false;
	if (pHead == NULL)
		pHead = pNode;
	else {
		if (DemX(pHead, Data) > 0) {
			return false;
		}
		else {
			pNode->pNext = pHead;
			pHead = pNode;
		}
	}
	return true;
}

/* 4. Chương trình mẫu cho phép thêm vào cuối danh sách liên kết đơn 1 giá trị nguyên.*/
bool AddTail(NODE*& pHead, int Data)
{
	NODE* pNode = new NODE;
	pNode = CreateNode(Data);
	if (pNode == NULL)
		return false;
	if (pHead == NULL)
		pHead = pNode;
	else
	{
		if (DemX(pHead, Data) > 0) {
			return false;
		}
		else {
			NODE* pNew = pHead;
			while (pNew != NULL && pNew->pNext != NULL)
				pNew = pNew->pNext;
			pNew->pNext = pNode;
		}
	}
	return true;
}

/* Hàm nhập dữ liệu cho DSLK*/
void Nhap(NODE*& pRoot) {
	int Data;
	do
	{
		cout << "Nhap vao du lieu, -1 de ket thuc: ";
		cin >> Data;
		if (Data == -1)
			break;
		AddHead(pRoot, Data);
	} while (Data != -1);
}

/* 9. Cho sẵn một danh sách liên kết đơn gồm các phần tử mang giá trị nguyên và một giá trị nguyên
x. Hãy tách danh sách liên kết đã cho thành 2 danh sách liên kết: một danh sách gồm các phần tử có
giá trị nhỏ hơn giá trị x và một danh sách gồm các phần tử có giá trị lớn hơn giá trị x. Giải quyết
trong 2 trường hợp:
*/
/* a.Danh sách liên kết ban đầu không cần tồn tại. */
void A_Two_Node(NODE* pHead, NODE*& pLeft, NODE*& pRight, int x) {
	NODE* pNode = pHead;
	while (pNode != NULL) {
		if (pNode->Key < x) {
			AddHead(pLeft, pNode->Key);
		}
		else if (pNode->Key > x) {
			AddHead(pRight, pNode->Key);
		}
		pNode = pNode->pNext;
	}
}
/* b. Danh sách liên kết ban đầu bắt buộc phải tồn tại. */
void B_Two_Node(NODE*& pHead, NODE*& pLeft, NODE*& pRight, int x) {
	NODE* pNode = pHead;
	if (pNode == NULL) {
		cout << "\nDanh sach rong! Vui long nhap du lieu." << endl;
		Nhap(pNode);
	}
	while (pNode != NULL) {
		if (pNode->Key < x) {
			AddHead(pLeft, pNode->Key);
		}
		else if (pNode->Key > x) {
			AddHead(pRight, pNode->Key);
		}
		pNode = pNode->pNext;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	NODE* pRoot;
	//Ghi chu: Tại sao lại phải thực hiện phép gán phía dưới? --> tạo một not mới đầu danh sách để thực hiện các phép nhập xuất
																//và tính toán trong danh sách
	pRoot = NULL;
	int Data;
	Nhap(pRoot);
	system("cls");//lệnh xóa màn hình
	cout << "\nDu lieu da duoc nhap: ";
	if (pRoot == NULL) {
		cout << "Ban chua nhap du lieu.";
	}
	else {
		//Ghi chu: Chức năng của dòng lệnh phía dưới: In tất cả các giá trị có trong danh sách liên kết
		PrintList(pRoot);
	}

	cout << "\n-----------------------  Lua Chon ----------------------------" << endl;
	cout << "1. Tinh tong gia tri cac phan tu danh sach lien ket don.		" << endl;
	cout << "2. Gia tri nguyen lon nhat trong danh sach lien ket don.		" << endl;
	cout << "3. So luong cac phan tu danh sach lien ket don.				" << endl;
	cout << "4. Them vao cuoi danh sach lien ket don 1 gia tri nguyen.		" << endl;
	cout << "5. Xoa phan tu dau danh sach lien ket don.						" << endl;
	cout << "6. Xoa phan tu cuoi danh sach lien ket don.						" << endl;
	cout << "7. So luong cac phan tren DSLK don trung voi gia tri x cho truoc.	" << endl;
	cout << "8. Tach DSLK theo x.											" << endl;
	cout << "--------------------------------------------------------------" << endl;

	int luachon;
	do {
		cout << "\nChon menu, -1 de ket thuc: ";
		cin >> luachon;
		if (luachon == 1)
		{
			cout << "1. Tong gia tri cac phan tu tren danh sach lien ket don la: " << SumList(pRoot) << endl;
		}
		else if (luachon == 2)
		{
			cout << "2. Gia tri nguyen lon nhat la: " << MaxList(pRoot) << endl;
		}
		else if (luachon == 3)
		{
			cout << "3. So luong cac phan tu cua danh sach lien ket don: " << CountList(pRoot) << endl;
		}
		else if (luachon == 4)
		{
			//them cuoi danh sach
			cout << "4. Nhap gia tri muon them vao cuoi danh sach: ";
			cin >> Data;
			AddTail(pRoot, Data);
			cout << "Danh sach lien ket sau khi them " << Data << " vao cuoi danh sach" << endl;
			PrintList(pRoot);
			cout << endl;
		}
		else if (luachon == 5) {
			//xoa phan tu dau danh sach
			XoaDau(pRoot);
			cout << "5. Danh sach lien ket sau khi xoa phan tu dau: ";
			PrintList(pRoot);
			cout << endl;
		}
		else if (luachon == 6) {
			//xoa phan tu cuoi danh sach
			XoaCuoi(pRoot);
			cout << "6. Danh sach lien ket sau khi xoa phan tu cuoi: ";
			PrintList(pRoot);
			cout << endl;
		}
		else if (luachon == 7) {
			//so luong phan tu trung
			int x = 4;
			cout << "\nx = " << x;
			cout << "7. Co " << DemX(pRoot, x) << " phan tu trong danh sach lien ket mang gia tri " << x << endl;
		}
		else if (luachon == 8) {
			NODE* pTest;//danh sach tach theo x
			NODE* pLeft;// danh sach phan tu nho hon gia tri x
			NODE* pRight;// danh sach phan tu lon hon gia tri x
			pTest = NULL, pLeft = NULL, pRight = NULL;

			int a[10] = { 1, 2, 8, 3, 9, 3, 25, 76, 34, 100 };
			for(int i = 0; i < size(a); i++){
				AddHead(pTest, a[i]);
			}

			cout << "\n----------- Chon a hoac b -----------------------";
			cout << "\n a. Danh sach lien ket ban dau khong can ton tai.";
			cout << "\n b. Danh sach lien ket ban dau bat buoc phai ton tai.";
			cout << "\n-------------------------------------------------";
			string chon;
			do {
				cout << "\nChon, -1 de thoat: ";
				cin >> chon;
				if (chon == "a" || chon == "b") {
					cout << "\nBan da chon : " << chon;
				}
				if (chon == "a")
				{
					int x;
					cout << "\nNhap x: ";
					cin >> x; 

					A_Two_Node(pRoot, pLeft, pRight, x);
					/*In ra cac gia tri nho hon x*/
					if (pLeft == NULL) {
						cout << "\nGia tri cac phan tu nho hon " << x << " la: khong co gia tri nao nho hon " << x;
					}
					else {
						cout << "\nGia tri cac phan tu nho hon " << x << " la: ";
						PrintList(pLeft);
					}
					/*In ra cac gia tri lon hon x*/
					if (pRight == NULL) {
						cout << "\nGia tri cac phan tu lon hon " << x << " la: khong co gia tri nao lon hon " << x;
					}
					else {
						cout << "\nGia tri cac phan tu lon hon " << x << " la: ";
						PrintList(pRight);
						cout << endl;
					}
				}
				else if (chon == "b") {
					int x;
					cout << "\nNhap x: ";
					cin >> x;

					B_Two_Node(pRoot, pLeft, pRight, x);
					/*In ra cac gia tri nho hon x*/
					if (pLeft == NULL) {
						cout << "\nGia tri cac phan tu nho hon " << x << " la: khong co gia tri nao nho hon " << x;
					}
					else {
						cout << "\nGia tri cac phan tu nho hon " << x << " la: ";
						PrintList(pLeft);
					}
					/*In ra cac gia tri lon hon x*/
					if (pRight == NULL) {
						cout << "\nGia tri cac phan tu lon hon " << x << " la: khong co gia tri nao lon hon " << x;
					}
					else {
						cout << "\nGia tri cac phan tu lon hon " << x << " la: ";
						PrintList(pRight);
						cout << endl;
					}
				}
				else if (chon == "-1")
					break;
				else {
					cout << "\nVui long nhap ky tu a, b hoac -1!";
				}
			} while (chon != "a" || chon != "b" || chon != "-1");
		}
		else if (luachon == -1)
			break;
		else {
			cout << "Ban nhap lua chon khong dung! Vui long nhap lai" << endl;
		}
	} while (luachon != -1);

	//Ghi chu : Chức năng của dòng lệnh phía dưới: Xóa tất cả các giá trị có trong danh sách liên kết
	RemoveAll(pRoot);
	return 0;
}
/*
1. Biên dịch đoạn chương trình trên -> đã biên dịch
2. Kết quả màn hình khi nhập các dữ liệu sau:
-----Nhập -1:
		Du lieu duoc nhap la:

-----Nhập 5 -1:
		Du lieu duoc nhap la:
			5

-----Nhập 7 10  -23 -25 -4 1 -1:
		Du lieu duoc nhap la:
			1 -4 -25 -23 10 7

-----Nhập 1 2 3 4 -1
		Du lieu duoc nhap la:
			4 3 2 1

3. Nhận xét:  thứ tự nhập dữ liệu nhập vào với thứ tự in dữ liệu ra màn hình khác nhau,
tức in ngược với thứ tự nhập, nhập trước thì in sau,
Do sử dụng hàm AddHead để thêm giá trị vừa nhập(nếu thỏa yêu cầu) vào đầu node, nên node đang ở vị trí đầu sẽ
chuyển tới vị trí kế tiếp. Hàm PrinList in các node từ vị trí đầu đến vị trí cuối và dừng khi null.

4. Vẽ hình danh sách liên kết theo dữ liệu ở câu 2.

---Nhập -1:      |x|-|-->|x|
---Nhập 5 -1           |5|-|-->|X|
---Nhập 7 10 -23 -25 -4 1 -1:       |1|-|--> |-4|-|--> |-25|-|--> |-23|-|--> |10|-|--> |7|-|--> |X|

5. Nếu 2 dòng lệnh PrintList(pRoot) và RemoveAll(pRoot) hoán đổi vị trí thì khi xuất kết quả danh sách
vừa nhập không được in ra màn hình.
-->Vì: Hàm RemoveAll(pRoot) đã xóa hết các giá trị có trong danh sách trước khi được hàm PrintList(pRoot) in ra.

6. Nếu hàm main (_tmain) vòng lặp do...while được thay đổi như:
	do{
		printf("Nhap vao du lieu, -1 de ket thuc: ");
		scanf("%d", &Data);
		if(Data == -1)
			break;
	}while (Data != -1);
Dữ liệu được in ra màn hình là trống
Vd: nhập 1 2 3 4 -1 --> Du lieu duoc nhap la: -1 4 3 2 1
Lý do: do không có hàm Addhead(pRoot, Data) để thêm các giá trị Data vừa nhập
vào danh sách liên kết.

7.
---Hàm CreateNode(int Data) trả về con trỏ cấu trúc node có địa chỉ ô nhớ của
node mới được tạo ra chứa thông tin Data.

8. Ghi chú các dòng lệnh

9. Kết quả: báo lỗi không đọc được dữ liệu, do pHead đã bị xóa.

10.  Gía trị cuối cùng của biến pRoot trong đoạn chương trình mẫu là null,
do đã thực hiện hàm RemoveAll(pRoot) (xóa tất cả các giá trị trong danh sách)

*/