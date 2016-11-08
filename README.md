# 도서관 관리 프로그램

프로그래밍 2 및 실습 - 프로젝트(도서관 서비스 프로그램) 사용 능력을 배양한다.

◎ 목적 : 도서관 서비스 프로그램 개발을 통해 동적 메모리 할당, 자기 참조 구조체, 파일 입출력 ◎ 프로젝트는 3인 혹은 4인으로 구성되며, 단독으로 제출할 경우 만점의 70%만 부여된다.◎ 제출물 : 하드카피(함수 설명, 실행 화면, 참여자들의 작업 분배 항목과 비율 명확히 명시)            소스코드 및 데이터 파일 이메일 제출(프로젝트 검사 시 필요)    프로젝트 평가표(구현 항목에 O, 부분구현 및 미구현에 X 표기하여 제출. 부분구현과 미구현은 점수 없음)

◎ 프로젝트 마감일 : 12월 둘째 주(5, 9일 실습 시간)

◎ 카피본 발견 시 소스 제공 팀과 함께 0점 처리. 유사도 검사 프로그램으로 카피본 검사 예정.1. 파일 목록

• 고객, 도서, 대여 관리를 위해 텍스트 파일인 client, book, borrow 파일을 만든다. 각 파일은 다음과 같은 정보를 저장한다. 

- client 파일

고객 정보를 저장하기 위한 파일이며, 프로젝트 검사 시 최소 30명 이상의 정보가 포함되어 있어야 한다. 저장되는 정보는 학번(정수 8자리), 비밀번호(문자열), 이름(문자열), 주소(문자열), 전화번호(문자열) 이다.

- book 파일

도서 목록을 저장하기 위한 파일이며, 프로젝트 검사 시 최소 100권 이상의 정보가 포함되어 있어야 한다. 저장되는 정보는 도서번호(정수 7자리), 도서명(문자열), 출판사(문자열), 저자명(문자열), ISBN(정수 13자리), 소장처(문자열), 대여가능 여부(문자) 이다.- borrow 파일

대여 목록을 저장하기 위한 파일이며, 프로젝트 검사 시 최소 20건 이상의 정보가 포함되어 있어야 한다. 저장되는 정보는 학번(정수 8자리), 도서번호(정수 7자리), 대여일자(time_t 형), 반납일자(time_t 형) 이다.

• 파일과 관련하여 다음과 같은 요구사항을 만족해야 한다.

1. 파일에 저장된 정보는 프로그램을 실행하면 바로 메모리에 로드되어 관리한다.2. 회원은 학번으로 정렬하여 저장한다. 즉, 관리자 메뉴에서 회원 보기를 하면 학번 순으로 정렬되어 출력되어야 하고, client 파일에도 학번 순으로 저장되어야 한다.3. 도서는 ISBN 숫자로 정렬하여 저장한다. 즉, 도서목록 보기를 선택하면 ISBN 순으로 정렬되어 출력되어야 하고, book 파일에도 ISBN 순으로 저장되어야 한다.4. 파일에 저장되는 각 정보들은 | 문자로 구분하여 저장한다. 

   예) 20102401 | com2401 | 홍길동 | ......

5. 도서번호는 같은 도서가 여러 권 존재할 수 있으므로 반드시 서로 다른 값을 가지며, 소장처는 도서가 비치된 위치를 의미한다. 

6. 이미 대여된 도서의 경우, 대여가능 여부는 N, 그렇지 않을 경우에는 Y 값을 갖는다.7. 반납일자는 대여일자 + 30 일에 해당한다. 만일 30일째 되는 날이 일요일이면 반납일자는 대여일자 + 31 일에 해당한다.

8. 학번, 도서번호는 각 파일에서 중복된 값을 가질 수 없다.

9. 회원 등록, 도서 등록, 도서 대여, 도서 반납, 도서 삭제 등 파일의 내용이 변경되는 액션이 일어나면 즉시 파일에 그 내용을 써야한다.

※ 파일로부터 정보를 읽어올 때에는 동적메모리 할당 기법과 자기 참조 구조체를 사용하여 구현해야 높은 점수를 받을 수 있다.

 

2. 프로그램 명세

로그인 정보를 가지고 구분한다. 

• 도서관 서비스 프로그램은 회원용과 관리자용 기능을 제공해야 하며, 회원용과 관리자용 구분은 • 회원용으로 로그인하면, 도서검색, 자신의 대여목록, 개인정보수정, 회원탈퇴, 등의 기능을 제공• 관리자용으로 로그인하면, 도서등록, 도서삭제, 도서대여, 도서반납, 도서검색, 회원목록, 등의 • 프로그램을 시작하면 다음과 같은 초기 메뉴를 출력해야 한다.

기능을 제공하야 한다.

해야 한다.

>> 도서관 서비스 <<

1. 회원 가입2. 로그인   3. 프로그램 종료

- 1을 입력하면 회원가입을 학번, 비밀번호, 이름, 주소, 전화번호를 입력받아 그 정보를 client 파일에 저장한다. 만일 동일한 학번이 이미 있으면 오류메시지를 출력해야 하고, 아니면 학번순으로 정렬하여 저장해야 한다. 회원 가입이 완료되면 초기 메뉴로 돌아가야 한다.- 2를 입력하면 로그인명과 비밀번호를 입력받는다. 만일 로그인명으로 학번이 입력되면 회원용으로, 또는 admin이 입력되면 관리자용으로 실행한다.

- 3을 입력하면 프로그램을 종료한다.

• 회원용과 관리자용의 자세한 세부 메뉴는 다음과 같다.

1) 회원용

• 회원용의 초기 메뉴는 다음과 같다.

>> 회원 메뉴 <<

1. 도서 검색2. 내 대여 목록

3. 개인정보 수정4. 회원 탈퇴

5. 로그아웃6. 프로그램 종료

• 회원용 도서 검색 메뉴는 다음과 같은 서브 메뉴를 갖는다.

>> 도서 검색 <<

1. 도서명 검색2. 출판사 검색

3. ISBN 검색4. 저자명 검색

5. 전체 검색   6. 이전 메뉴

도서명 검색을 선택하고 도서명을 입력하면 전체 도서목록 중 입력된 이름에 해당하는 도서 정보를 출력한다. 도서 정보에는 도서명, 출판사, 저자명, ISBN, 소장처, 대여가능 여부가 포함된다. 아울러 출판사, ISBN, 저자명 검색을 지원하며 결과는 도서명 검색과 동일하다. 전체 검색은 book 파일에 저장되어 있는 모든 도서들의 정보가 출력된다. 이전메뉴를 선택하면 회원용 메뉴로 돌아가야 한다.

>> 내 대여 목록 <<

자신이 대여 받은 도서 정보가 출력된다. 도서번호, 도서명, 대여일자, 반납일자가 출력된다.>> 개인정보 수정 <<

학번과 이름을 제외한 모든 정보를 수정할 수 있다. 수정 후에는 그 결과를 client 파일에 저장해야 한다.

>> 회원탈퇴 <<

회원탈퇴는 대여중인 도서목록이 없을 때만 가능하다. 회원탈퇴 시 client 파일에서 해당 회원의 정보가 삭제된다.

- 로그아웃을 선택하면 도서관 서비스 초기 화면으로 이동한다.

- 프로그램 종료를 선택하면 도서관 서비스 프로그램이 종료된다.

 

2) 관리자용

• 관리자용의 초기 메뉴는 다음과 같다.

>> 관리자 메뉴 <<

1. 도서 등록2. 도서 삭제

3. 도서 대여4. 도서 반납

5. 도서 검색6. 회원 목록

7. 로그아웃8. 프로그램 종료

>> 도서 등록 <<

관리자는 새로운 도서를 등록할 때 도서명, 출판사, 저자명, ISBN, 소장처를 입력한다. 등록되는 도서는 대여가능 여부가 Y, 도서번호는 마지막으로 등록된 도서의 도서번호 + 1이 되며, 관리자 프로그램이 자동으로 처리한다. 도서 등록이 완료되면 그 결과를 book 파일에 저장해야 한다.>> 도서 삭제 <<

등록된 도서를 삭제할 때에는 먼저 도서명 검색이나 ISBN 검색으로 삭제할 도서를 검색한다. 검색된 결과에는 도서번호, 도서명, 출판사, 저자명, ISBN, 소장처, 삭제 가능 여부(대여 가능 여부가 N이면 삭제 가능 여부는 N, 대여 가능 여부가 Y이면 삭제 가능 여부는 Y)가 출력된다. 삭제 시에는 검색된 도서 번호를 입력하며, 만일 대여 중인 경우에는 삭제할 수 없다. 도서가 삭제되면 그 결과를 book 파일에 저장해야 한다.

>> 도서 대여 <<

도서를 대여해 줄 때에는 먼저 도서명 검색이나 ISBN 검색으로 대여해 줄 도서를 검색한다. 검색된 결과에는 도서번호, 도서명, 출판사, 저자명, ISBN, 소장처, 대여 가능 여부가 출력된다. 관리자는 학번과 도서번호만을 입력하며, 관리자 프로그램은 자동으로 대여일자와 반납일자를 저장한다. 또한 대여된 도서는 대여 가능 여부가 N으로 변경된다. 도서가 대여되면 그 결과를 book 파일과 borrow 파일에 저장해야 한다.

>> 도서 반납 <<

회원이 도서를 반납할 때 관리자는 학번을 입력하며, 이 때 관리자 프로그램은 해당 회원의 모든 도서 대여 목록을 출력한다. 도서 대여 목록이 출력된 후, 관리자가 도서번호를 입력하면 도서 반납이 처리된다. 이 때, borrow 파일에서 도서 대여 정보가 삭제된다. 반납된 도서는 다른 회원이 대여할 수 있도록 대여 가능 여부가 Y로 변경된다. 반납이 처리되면 그 결과를 book 파일과 borrow 파일에 저장해야 한다.

>> 도서 검색 <<

회원 서비스의 도서 검색과 동일하다.

>> 회원 목록 <<

1. 이름 검색2. 학번 검색

3. 전체 검색4. 이전 메뉴

이름 검색을 선택하고 이름을 입력하면, 해당 회원의 학번, 이름, 주소, 전화번호 정보가 출력된다. 학번 검색의 출력결과도 이름 검색과 동일하다. 전체 검색은 client 파일에 저장되어 있는 모든 회원의 학번, 이름, 주소, 전화번호 정보가 출력된다.

 

3. 회원용 서비스 화면 구성 예

>>  도서관  서비스  <<

1.  회원  가입                      2.  로그인                      3.  프로그램  종료번호를  선택하세요: 1

>>  회원  가입  <<

학번,  비밀번호,  이름,  주소,  전화번호를  입력하세요.

학번: 20102401

비밀번호: com2401

이름:  홍길동

주소:  서울시  동작구  상도동  숭실대학교

전화번호: 01012345678

회원가입이  되셨습니다.

>>  로그인  <<

학번: 20102401

비밀번호: com2401

>>  회원  메뉴  <<

1.  도서  검색                      2.  내  대여  목록

3.  개인정보  수정              4.  회원  탈퇴

5.  로그아웃                        6.  프로그램  종료

번호를  선택하세요: 1

>>  도서  검색  <<

1.  도서명  검색                      2.  출판사  검색

3. ISBN  검색                        4.  저자명  검색

5.  전체  검색                          6.  이전  메뉴

번호를  선택하세요: 1

도서명을  입력하세요: 1Q84

>>  검색  결과  <<

도서명: 1Q84

출판사:  문학동네

저자명:  무라카미  하루키

ISBN: 9788954611800

소장처:  중앙도서관  4층  인문과학실

대여가능  여부: N(2/2)

** Y는 대여가능, N은 대여불가를 의미

** (x/y) : (대여된 총 권수 / 보유하고 있는 총 권수)

>>  도서  검색  <<

1.  도서명  검색                      2.  출판사  검색

3. ISBN  검색                        4.  저자명  검색

5.  전체  검색                          6.  이전  메뉴

번호를  선택하세요: 6

>>  회원  메뉴  <<

1.  도서  검색                      2.  내  대여  목록

3.  개인정보  수정              4.  회원  탈퇴

5.  로그아웃                        6.  프로그램  종료

번호를  선택하세요: 2

>>  내  대여  목록  <<

도서번호: 1468212

도서명: 1Q84

대여일자: 2010년 10월 29일  금요일

반납일자: 2010년 11월 29일  월요일

도서번호: 1434710

도서명:  정의란  무엇인가

대여일자: 2010년 10월 28일  목요일

반납일자: 2010년 11월 27일  토요일

 

4. 관리자용 서비스 샘플

>>  도서관  서비스  <<

1.  회원가입                      2.  로그인                      3.  프로그램  종료번호를  선택하세요: 2

>>  로그인  <<

학번: admin

비밀번호: lib_admin7

>>  관리자  메뉴  <<

1.  도서  등록                      2.  도서  삭제

3.  도서  대여                      4.  도서  반납

5.  도서  검색                      6.  회원  목록

7.  로그아웃                        8.  프로그램  종료

번호를  선택하세요: 1

>>  도서  등록  <<

도서명: Cygwin과  함께  배우는 C  프로그래밍

출판사:  홍릉과학출판사

저자명:  김명호

ISBN: 9788972838173

소장처:  중앙도서관  3층  자연과학실

자동입력  사항

대여가능  여부: Y

도서번호: 1468213

등록하시겠습니까? Y

>>  관리자  메뉴  <<

1.  도서  등록                      2.  도서  삭제

3.  도서  대여                      4.  도서  반납

5.  도서  검색                      6.  회원  목록

7.  로그아웃                        8.  프로그램  종료

번호를  선택하세요: 2

>>  도서  삭제  <<

1.  도서명  검색              2. ISBN  검색

검색  번호를  입력하세요: 1

도서명을  입력하세요: 1Q84

>>  검색  결과  <<

도서번호: 1468212(삭제  가능  여부 : N), 1455434(삭제  가능  여부 : Y)도서명: 1Q84

출판사:  문학동네

저자명:  무라카미  하루키

ISBN: 9788954611800

소장처:  중앙도서관  4층  인문과학실

삭제할  도서의  번호를  입력하세요: 1468212

이  도서는  삭제할  수  없습니다.

>>  관리자  메뉴  <<

1.  도서  등록                      2.  도서  삭제

3.  도서  대여                      4.  도서  반납

5.  도서  검색                      6.  회원  목록

7.  로그아웃                        8.  프로그램  종료

번호를  선택하세요: 3

>>  도서  대여  <<

1.  도서명  검색              2. ISBN  검색

검색  번호를  입력하세요: 2

ISBN을  입력하세요: 9788972838173

>>  검색  결과  <<

도서번호: 1468213(대여  가능  여부 : Y)

도서명: Cygwin과  함께  배우는 C  프로그래밍

출판사:  홍릉과학출판사

저자명:  김명호

ISBN: 9788972838173

소장처:  중앙도서관  3층  자연과학실

학번을  입력하세요: 20102401

도서번호를  입력하세요: 1468213

이  도서를  대여합니까? Y

도서가  대여  되었습니다.

>>  관리자  메뉴  <<

1.  도서  등록                      2.  도서  삭제

3.  도서  대여                      4.  도서  반납

5.  도서  검색                      6.  회원  목록

7.  로그아웃                        8.  프로그램  종료

번호를  선택하세요: 4

학번을  입력하세요: 20102401

>>  회원의  대여  목록  <<

도서번호: 1468212

도서명: 1Q84

대여일자: 2010년 10월 29일  금요일

반납일자: 2010년 11월 29일  월요일

도서번호: 1434710

도서명:  정의란  무엇인가

대여일자: 2010년 10월 28일  목요일

반납일자: 2010년 11월 27일  토요일

반납할  도서번호를  입력하세요: 1434710

도서  반납처리를  할까요? Y

도서가  반납  되었습니다.

 

과  목

프로그래밍  2  및  실습

프로젝트

점  수팀원1 학  번

팀원2 학  번

팀원3 학  번

팀원4 학  번

이  름

이  름

이  름

이  름

참여율참여율참여율참여율평  가  항  목(구현여부)

배점 평가점수1.  동적  메모리  할당  및  자기  참조구조체를  사용했는가? (    )

2.  대여일자와  반납일자가  제대로  구현되었는가? (    )

3.  모든  데이터들이  정렬되어  저장되고  출력  되는가? (    )

4.  회원  기능

4.1  회원  가입  기능이  구현되었는가? (    )

4.2  회원  탈퇴  기능이  구현되었는가? (    )

4.3  로그인  기능이  구현되었는가? (    )

4.4  개인  정보  수정  기능이  구현되었는가? (    )

4.5  도서  검색  기능이  구현되었는가? (    )

4.6  내  대여  목록  기능이  구현되었는가? (    )

5.  관리자  기능

5.1  도서  등록  기능이  구현되었는가? (    )

5.2  도서  삭제를  위한  검색  및  삭제  기능이  구현되었는가? (    )5.3  도서  대여를  위한  검색  및  대여  기능이  구현되었는가? (    )5.4  도서  반납을  위한  검색  및  반납  기능이  구현되었는가? (    )5.5  회원  목록  기능이  구현되었는가? (    )

6.  하드카피

6.1  함수  설명을  상세히  기록되었는가?

6.2  실행  화면  결과를  충분히  다양하게  제출하였는가?

6.3  작업분배  항목과  비율이  상세히  작성되었는가?

합              계

--------------------------------------------------------------------◎  참여율은  총  100%가  되게  명시해야  함.

