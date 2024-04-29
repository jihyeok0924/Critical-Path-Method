# Critical-Path-Method
## 개요
1. cpm이란?
2. 구현

2-1. 포인터의 활용
   
2-2. 동작할당의 활용
5. 작동 방법
6. 결과 사진

## CPM이란?
크리티컬 패스 분석법(Critical Path Method, CPM)은 프로젝트를 완료하는 데 필요한 작업을 식별하고 일정의 유연성을 판단하는 기술입니다. 프로젝트 관리에서 크리티컬 패스는 가장 경로(Path)가 긴 일련의 활동으로, 프로젝트 전체를 끝내기 위해 반드시 기한 내에 완료되어야 하는 활동입니다. 중요한 작업이 지연되면 나머지 프로젝트도 지연됩니다.
CPM은 프로젝트 타임라인에서 가장 중요한 작업을 발견하고, 작업 종속성을 파악하고, 작업 소요 기간을 계산하는 것이 핵심입니다.

크리티컬 패스 분석법을 사용해야 하는 이유는 다음과 같습니다.
향후 계획 개선: CPM은 실제 진행 상태와 기대치를 비교하는 데 사용할 수 있습니다. 현재 프로젝트에서 사용된 데이터를 향후 프로젝트 계획에 반영할 수 있습니다. 
더 효과적인 리소스 관리: CPM은 프로젝트 매니저가 작업 우선순위를 지정하는 데 도움이 되어 리소스를 어디에 어떻게 배치하면 좋을지 더 잘 파악할 수 있습니다. 
업무 지연 방지: 프로젝트가 지연되면 귀중한 시간을 낭비할 수 있습니다. 네트워크 다이어그램을 이용하여 프로젝트 종속성을 계획하면 병행할 수 있는 활동과 그렇지 않은 활동을 더 잘 파악하여 그에 따라 일정을 계획할 수 있습니다.   

크리티컬 패스를 찾는 방법
: 활동 목록 만들기, 작업 종속성 파악하기, 네트워크 다이어그램 생성하기, 작업 소요 기간 추정하기, 크리티컬 패스 계산하기, 플로트 계산하기

## 구현
본 프로젝트는 csv 파일로 정리한 활동 목록을 이용하여 크리티컬 패스를 계산하고 네트워크 다이어그램을 출력하는 것입니다. csv 파일에는 작업의 총 개수, 작업명, 작업 기간, 작업 소요비용, 종속된 작업 개수, 종속된 작업명을 포함합니다. 

### 포인터의 활용
- 포인터 배열 : Successors 및 Predecessors 배열은 각각 다음 활동 및 이전 활동을 나타냅니다. 이러한 배열들은 구조체 내에 포인터로 선언했습니다.

- 여러 함수들에서 포인터를 전달하고 반환 :  CheckActivity 함수는 포인터를 인자로 받고 check 포인터를 설정합니다. SetSuccessors 함수는 포인터를 사용하여 Successors 배열의 길이를 계산합니다. GetIndex 함수는 포인터를 사용하여 인덱스를 검색합니다.

- 파일 입출력 : fopen 함수를 사용하여 파일을 열고, 파일 포인터를 반환합니다.

### 동적할당의 활용
- 동적 메모리 할당: activityInstance는 GetActivities 함수 내에서 malloc 함수를 사용하여 동적할당을 이용합니다. Predecessors 배열의 요소들 또한 동적으로 할당했습니다. aux 변수도 malloc 함수를 사용하여 동적으로 할당했습니다.

- 동적 메모리 해제: main 함수의 끝에서 free 함수를 사용하여 List 배열에 할당된 메모리를 해제합니다.

## 작동 방법
1. 작업의 총 개수, 작업명, 작업 기간, 작업 소요비용, 종속된 작업 개수, 종속된 작업명을 포함한 csv 파일을 만듭니다.

2. csv 파일에 적혀있는 종속된 작업과 작업 기간을 통해 Earliest End Time, Earliest Start Time, Latest End Time, Latest Start Time을 계산합니다. 

3. 작업이 critical path에 포함되는지 확인하기위해 모든 작업을 순회하며, Est와 Lst, Eet와 Let가 일치하는지 확인합니다. 또한 모든 작업 소요비용을 더하여 총 소요 비용을 계산합니다.

4. 계산결과를 시각화하기 위해 그래프 구조로 표현하고, critical path는 특히 붉은 글씨로 표현합니다. 해당 시각화 결과를 graph.dot 파일로 저장합니다.

5. 터미널에서 .dot파일을 .png 파일로 저장합니다.

## 결과 사진
![graph](https://github.com/jihyeok0924/Critical-Path-Method/assets/144129774/526344db-5666-44ba-a780-80bd9e39cc1b)
