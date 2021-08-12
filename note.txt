1. access
#include <unistd.h>
int access(const char *pathname, int mode); 
 - 파일 또는 디렉토리의 사용자 권한 체크
 - mode 변수 mask 종류
	* F_OK : 파일 존재 여부
	* R_OK : 파일 존재 여부, 읽기 권한 여부
	* W_OK : 파일 존재 여부, 쓰기 권한 여부
	* X_OK : 파일 존재 여부, 실행 권한 여부
	* mode 변수가 들어갈 곳에 비트 연산으로 여러가지를 한번에 체크할 수 있다. (mode = R_OK | W_OK)
 - 리턴값
	* 성공하면 0, 실패하면 -1을 반환한다.

2. open
#include <fcntl.h>
int open(const char *path, int oflag, ...);

3. unlink
#include <unistd.h>
int unlink(const char *path);
 - 시스템 호출을 사용하여 파일에 대한 디렉토리 항목을 지우고 링크 개수를 감소 시킴
 - 해당 함수 사용을 위해서는 파일의 디렉토리 항목에 포함된 모든 디렉토리에 대해 쓰기, 실행 권한이 필요
 - 리턴값
	* 성공시 0, 실패시 -1

3. close
#include <unistd.h>
int close(int fildes);

4. read
#include <unistd.h>
ssize_t read(int fildes, void *buf, size_t nbyte);

5. write
#include <unistd.h>
ssize_t write(int fildes, const void *buf, size_t nbyte);

6. malloc
#include <stdlib.h>
void *malloc(size_t size);

7. waitpid
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *stat_loc, int options);
- 프로세스 종료 상태를 리턴해 주는 함수
- 자식 프로세스를 기다릴 때 사용하는 함수 (자식 프로세스의 종료 상태를 회수할 때 사용)
- wait함수와 다른 점 : 특정한 자식 프로세스를 기다리게 할 수 있다.
- waitpid 함수의 첫번째 인자
	* pid가 -1일 경우 (pid == -1) : 임의의 자식 프로세스를 기다림
	* pid가 0보다 클 경우 (pid > 0) : 프로세스 ID가 pid인 프로세스를 기다림
	* pid가 -1보다 작을 경우 (pid < -1) : 프로세스 그룹 ID가 pid의 절댓값과 같은 자식 프로세스를 기다림
	* pid가 0일 경우 (pid == 0) : waitpid를 호출한 프로세스의 프로세스 그룹 PID와 같은 프로세스 그룹 ID를 가진 프로세스를 기다림
- waitpid 함수의 두번째 인자
	* 자식 프로세스가 정상적으로 종료 : WIFEXITED(statloc) 매크로가 true를 반환
	* 자식 프로세스가 비정상적으로 종료 : WIFSIGNALED(statloc) 매크로가 true를 반환
								 비정상 종료 이유를 WTERMSIG(statloc) 매크로를 사용하여 구할 수 있음
	* waitpid 함수 오류 : ECHILD -> 호출자의 자식 프로세스가 없는 경우
						EINTR -> 시스템 콜이 인터럽트 되었을 때
- waitpid 함수의 세번째 인자
	* WCONTINUED : 중단 되었다가 재개된 자식 프로세스의 상태를 받음
	* WNOHANG : 기다리는 PID가 종료되지 않아서 즉시 종료 상태를 회수할 수 없는 상황에서 호출자는 차단되지 않고 반환값으로 0을 받음
	* WUNTRACED : 중단된 자식 프로세스의 상태를 받음
- 리턴값
	* 성공시 : 프로세스 ID
	* 오류 발생시 : -1
	* 그 외 : 0

8. wait
#include <sys/wait.h>
pid_t wait(int *stat_loc);
- 자식 프로세스 작업이 끝날 때까지 대기하며, 자식 프로세스가 종료한 상태를 구함.
- 인수 : 자식 프로세스 종료 상태
- 리턴값 : 종료된 자식 프로세스 ID
- stat_loc 매크로
	* WIFEXITED : 자식 프로세스가 정상적으로 종료되었다면 true
	* WIFSIGNALED : 자식 프로세스가 시그널에 의해 종료되었다면 true
	* WIFSTOPPED : 자식 프로세스가 중단되었다면 true
	* WEXITSTATUS : 자식 프로세스가 종료되었을 때 반환한 값
		ex) if (WIFEXITED(stat_loc))

9. fork
#include <unistd.h>
pid_t fork(void);
- 현재 실행되는 프로세스에 대해 복사본 프로세스를 생성.
- 부모 프로세스(원본 프로세스) : fork 함수의 반환값은 자식 프로세스의 ID
- 자식 프로세스(원본 프로세스에서 fork로 생성한 새로운 프로세스) : fork 함수의 반환값은 0
- 리턴값
	* 성공시 : 프로세스 ID 반환
	* 실패시 : -1

10. pipe
#include <unistd.h>
int pipe(int fildes[2]);
- 자식 프로세스가 생성하는 데이터를 실시간으로 읽는 방법
- 하나의 파이프 및 파이프에 대한 두 개의 파일 디스크립터가 생성
- 하나의 파이프를 프로세스들이 공유
- fd 2개를 저장할 배열을 인자로 넘겨준다. 한 배열에서는 파이프 읽기(read), 다른 하나에서는 파이프 쓰기(write)를 하는 fd가 생성.
	* fd[0] : 함수 호출 후 fd[0]에 데이터를 입력 받을 수 있는 파일 디스크립터가 담김(파이프 출구)
	* fd[1] : 함수 호출 후 데이터를 출력할 수 있는 파일 디스크립터다 담긴다(파이프 입구)
- 리턴값
	* 성공시 : 0
	* 실패시 : -1
- 파이프 특징
	* 파이프 자체는 fork함수에 의해 복사되지 않음
	* 파이프는 방향성이 존재하지 않음

11. dup
#include <unistd.h>
int dup(int fildes);
- files : 복사할 파일 디스크립터
- fd로 전달받은 파일 서술자를 복제하여 반환
- dup가 돌려주는 파일 서술자는 가장 낮은 서술자를 반환
- 리턴값
	* 성공시 : 새 파일 서술자
	* 오류시 : -1

12. dup2
#include <unistd.h>
int dup2(int fildes, int fildes2);
- files : 복사할 파일 디스크립터
- files2 : 복사된 파일 디스크립터 번호 
- 새 서술자의 값을 fd2로 지정
- 만약 fd2가 열려있을 시, fd2를 닫은 후 복제
- dup가 돌려주는 파일 서술자는 가장 낮은 서술자를 반환
- 리턴값
	* 성공시 : 새 파일 서술자
	* 오류시 : -1

13. execve
#include <unistd.h>
int execve(const char *path, char *const argv[], char *const envp[]);
- 다른 프로그램은 실행하고 자신은 종료
- 실행가능한 파일인 path의 실행코드를 현재 프로세스에 적재하여 기존의 실행코드와 교체하여 새로운 기능으로 실행
- 즉, 현재 실행되는 프로그램의 기능은 없어지고 path 프로그램을 메모리에 로딩해 처음부터 실행 
- path
	* 디렉토리 포함 전체 파일명 (교체할 실행 파일 / 명령어)
	* path는 실행가능한 binary이거나 shell
	* path는 경로가 설정되어 있는 디렉토리라고 하더라도 절대 경로나 상대 경로로 정확한 위치 지정 필요
- argv
	* 인수 목록
	* c언어의 main(int argc, char *argv[])에서 argv와 비슷하며, main함수에는 argc가 있지만 execve에는 argc가 없으므로 main의 argv에 마지막 array 다음은 NULL이어야 있는 것과 같다.
- envp
	* 환경 설정 목록
	* key=value형식의 환경변수 문자열 배열리스트로 마지막은 NULL이어야 함
- 리턴값
	* 없음
	* 바이너리 교체 실패 시 : -1 

14. perror
#include <stdio.h>
void perror(const char *s);
- 오류 메시지를 출력한다.
- 리턴값
	* 없음

15. strerror
#include <string.h>
char *strerror(int errnum);
- 인자를 오류 번호로 받아, 오류 메시지 문자열을 가리키는 포인터를 얻어온다.
- 리턴값
	* 오류 번호에 해당하는 오류 문자열을 가리키는 포인터 : 이때 리턴되는 포인터는 문자열 리터럴을 가리키고 있기 때문에 그 내용이 바뀔 수 없다.
	(strerror에 의해 출력되는 오류 메시지는 현재 사용중인 컴파일러나 플랫폼에 따라 다를 수 있다.)
