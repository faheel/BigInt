#include <climits>
#include <cmath>        // to check for conflicts
#include <cstdlib>      // for abs of integer types
#include <map>
#include <random>

#include "constructors/constructors.hpp"
#include "functions/conversion.hpp"
#include "functions/math.hpp"
#include "operators/binary_arithmetic.hpp"
#include "operators/io_stream.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Randomised test for abs()", "[functions][math][abs][random]") {
    std::random_device generator;
    // uniform distribution of numbers from INT_MIN to INT_MAX:
    std::uniform_int_distribution<int> distribution((INT_MIN), (INT_MAX));
    for (size_t i = 0; i < 20; i++) {
        int rand_num = distribution(generator);

        REQUIRE(abs(BigInt(rand_num)) == abs(rand_num));
    }
}

TEST_CASE("abs() of big integers", "[functions][math][abs][big]") {
    BigInt big_num, big_num_abs;
    big_num = "-26344012632774350668411924807957373509352408071007389017455689"
            "236404655575154572365301366147824648152450898838528";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);

    big_num = "-46669885189331860769155450438595342487131957776382953797715099"
            "97938259302930977527191562288518931563246478196696588932557954671"
            "067814675528299452793998233";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);

    big_num = "157624825433230490762246168127797657567916321816555529634539929"
            "03324298954062642979937715273000088457741871468238391929188212688"
            "34763045702038940236225905428806452453734203942833503591091652111"
            "6269942";
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == big_num);

    big_num = -big_pow10(12345);
    big_num_abs = abs(big_num);
    REQUIRE(big_num_abs == -big_num);
    REQUIRE(big_num == -big_num_abs);
}

TEST_CASE("Randomised test for big_pow10()", "[functions][math][big_pow10][random]") {
    std::random_device generator;
    // uniform distribution of numbers from 0 to SHRT_MAX:
    std::uniform_int_distribution<short> distribution(0, (SHRT_MAX));
    BigInt big_num;
    for (size_t i = 0; i < 20; i++) {
        short rand_exponent = distribution(generator);

        big_num = big_pow10(rand_exponent);
        REQUIRE(big_num.to_string() == "1" + std::string(rand_exponent, '0'));
    }
}

TEST_CASE("Base cases for pow()", "[functions][math][pow]") {
    // 0^-1
    try {
        BigInt undefined = pow("0", -1);
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Cannot divide by zero"));
    }
    // 0^0
    try {
        BigInt undefined = pow("0", 0);
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Zero cannot be raised to zero"));
    }
    REQUIRE(pow("0", 1) == 0);

    REQUIRE(pow("1", -1) == 1);
    REQUIRE(pow("1",  0) == 1);
    REQUIRE(pow("1",  1) == 1);

    REQUIRE(pow("-1", -1) == -1);
    REQUIRE(pow("-1",  0) ==  1);
    REQUIRE(pow("-1",  1) == -1);
}

TEST_CASE("pow() with BigInt base", "[functions][math][pow]") {
    BigInt num = 11;
    REQUIRE(pow(num, 9) == 2357947691);
    num = -27;
    REQUIRE(pow(num, 16) == "79766443076872509863361");
    num = 174;
    REQUIRE(pow(num, 28) == "5437245617739465972266838607094505258676301045444"
            "37723753086976");
    num = -491;
    REQUIRE(pow(num, 37) == "-371548240109793740704290562371939047874194757847"
            "1192936297400283387941819501964796887819867312404731");
    num = 1023;
    REQUIRE(pow(num, 46) == "2846290024820164306745254023122897258831206069504"
            "52318727969325369627171330538069500151925066426445843470621595871"
            "3707938963481435378239489");
    num = 4375;
    REQUIRE(pow(num, 123) == "692310717819222208645161329095927823458583641636"
            "03066687435794320395447971353935391209371822096875547147598543448"
            "58063013174221664072185139386716890286845284676429789376563237238"
            "21459181898500562615895709403045506146216402709302426975054984542"
            "82379017830901385909952557690741598760150017980773176849657658609"
            "10586786816268615033415630313626104634807563914442755557232584312"
            "26509067923785919654249933510544497833327781677326129283756017684"
            "9365234375");
}

TEST_CASE("pow() with integer base", "[functions][math][pow][integer]") {
    long long num = 8;
    REQUIRE(pow(num, 243) == "282401395870821749694910884220462786335135391185"
            "15775246834019308626938303611984999058739209952299969708978654982"
            "83996578123296865878390947626553088486946106430796091482716120572"
            "632072492703527723757359478834530365734912");
    num = 17;
    REQUIRE(pow(num, 180) == "302556054495901008313865017376163772741128463628"
            "48452051025575455414421375942025507613042229017536765822671493394"
            "40537573230160088368322808488281205414553961324252387686780177230"
            "68038205330113241354524959622306238937774401");
    num = -36;
    REQUIRE(pow(num, 101) == "-15365708057232986428691096094675854364347594832"
            "76161946183724684166406546378631060468659701626725550268526135680"
            "0340673914360748658633428725824561309114433536");

    REQUIRE(pow(729LL, 76) == "36922589523355488684862534309606828646354858539"
            "33963934010870460686027831695461222301192671449678638056692404147"
            "21568131470582838371860677594255943413907726272489256364738940659"
            "00906894946778020270362243511617241359521");
    REQUIRE(pow(-1850LL, 58) == "313299893588550378338834564511940091616782930"
            "14291813764729089755365285020953460978062715434205864895034210348"
            "96746277809143066406250000000000000000000000000000000000000000000"
            "000000000000000");
    REQUIRE(pow(24137LL, 41) == "489795632015614011122175981066754073282443339"
            "39948728458482169347805105319057028172299652278979515526555801382"
            "58256121841619802351764133789272763824594104080192254353037855728"
            "51337");
}

TEST_CASE("pow() with string base", "[functions][math][pow][string]") {
    std::string num = "15";
    REQUIRE(pow(num, 123) == "456273098478477754404871005449560512605808364897"
            "24452716204137204571502556329707022452196723171746311478388924420"
            "81260014674626290798187255859375");
    num = "-88";
    REQUIRE(pow(num, 164) == "785521782697551570945213155401580125421956658055"
            "48056598286634052504685584559003178242649146182814285551395798811"
            "29890198190577602637561754093202322057553543500267662416964728626"
            "54494995542956033916131308760564271808039033231156701241088535498"
            "29292323451578980827379278634804533636440616602433612705235954452"
            "67842727936");
    num = "673";
    REQUIRE(pow(num, 52) == "1139681082871140385901008482666731136077952234110"
            "74666715735678345006314459593056186063405561967228331677630675442"
            "0305995142114939236011090500616321");

    REQUIRE(pow("-5910", 43) == "-15075151241473776392006616026709431326069411"
            "51733898273297153829578658680990568795886085039857755798881149863"
            "719608986710000000000000000000000000000000000000000000");
    REQUIRE(pow("23487", 30) == "133298859471971822367112923632999128200430350"
            "37609890954320285896334527706015249826664957980123680633865514789"
            "2297850894367261618049");
    REQUIRE(pow("524356", 27) == "26909679757739832146190247401059923715257013"
            "08862990907940498760592041482791966715057053380053636634477979263"
            "4601932346249911644260403539535769743430516736");
}

TEST_CASE("Base cases for sqrt()", "[functions][math][sqrt]") {
    BigInt num = 0;
    REQUIRE(sqrt(num) == 0);
    num = 1;
    REQUIRE(sqrt(num) == 1);
    num = 3;
    REQUIRE(sqrt(num) == 1);
    num = 4;
    REQUIRE(sqrt(num) == 2);
    num = 9;
    REQUIRE(sqrt(num) == 3);
    num = 10;
    REQUIRE(sqrt(num) == 3);

    num = -1;
    try {
        BigInt undefined = sqrt(num);
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Cannot compute square root of a negative integer"));
    }
}

TEST_CASE("sqrt() of perfect squares", "[functions][math][sqrt]") {
    std::map<int, int> sqrt_map = {
            {4,        2},
            {9,        3},
            {16,       4},
            {25,       5},
            {36,       6},
            {49,       7},
            {64,       8},
            {81,       9},
            {100,      10},
            {121,      11},
            {144,      12},
            {169,      13},
            {196,      14},
            {225,      15},
            {256,      16},
            {1024,     32},
            {1046529,  1023},
            {1048576,  1024},
            {6086089,  2467},
            {6091024,  2468},
            {11703241, 3421},
            {11710084, 3422},
            {25969216, 5096},
            {25979409, 5097},
    };

    for (auto sqrt_pair : sqrt_map) {
        REQUIRE(sqrt(BigInt(sqrt_pair.first)) == sqrt_pair.second);
    }
}

TEST_CASE("Randomised test for sqrt()", "[functions][math][sqrt][random]") {
    std::random_device generator;
    // uniform distribution of numbers from 0 to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution(0, (LLONG_MAX));
    for (size_t i = 0; i < 100; i++) {
        long long rand_num = distribution(generator);

        REQUIRE(sqrt(BigInt(rand_num)) == (long long) sqrt(rand_num));
    }
}

TEST_CASE("sqrt() of big integers", "[functions][math][sqrt][big]") {
    BigInt num = 81224;
    REQUIRE(sqrt(num) == 284);

    num = 2802961249;
    REQUIRE(sqrt(num) == 52943);

    num = "24465964562071830625";
    REQUIRE(sqrt(num) == 4946308175);

    num = "3479680743635798438602889954485038919559460388450";
    REQUIRE(sqrt(num) == "1865390238967653234193278");

    num = "34194353721643989214042055879801028224577442242064";
    REQUIRE(sqrt(num) == "5847593840345273947234580");

    num = "4713365177845202127969377413966864031679429777731216458034793396477"
          "37161";
    REQUIRE(sqrt(num) == "686539523832765372419381874316283619");

    num = "3049530077087685856458276451272326319423080138439655574506776710873"
          "91006548030000";
    REQUIRE(sqrt(num) == "17462903759362833573945713140457169848645");

    num = "1208006135370083192366171536761431070551010018430168557130297136814"
          "124413249425830934603622833272936";
    REQUIRE(sqrt(num) == "34756382656572349234723593456269236723897234598723");

    num = "5396259133865814201706389193200689822711586341557906061174319731059"
          "5624546190598499053664826956154825894621643111076086259061529893859"
          "072147579231493639756755211658494550031529896427679216992311649649";
    REQUIRE(sqrt(num) == "7345923450367430967234547374457324572368945609486134"
            "098523490875239876209348752098273450239487562343");
}


long long gcd(long long a, long long b) {
    return a == 0 ? llabs(b) : gcd(b % a, a);
}

TEST_CASE("Randomised test for gcd()", "[functions][math][gcd][random]") {
    std::random_device generator;
    // uniform distribution of numbers from LLONG_MIN to LLONG_MAX:
    std::uniform_int_distribution<long long> distribution((LLONG_MIN), (LLONG_MAX));
    for (size_t i = 0; i < 100; i++) {
        long long integer1 = distribution(generator);
        long long integer2 = distribution(generator);


        BigInt big_int1 = integer1;
        BigInt big_int2 = integer2;
        std::string integer2_str = std::to_string(integer2);

        long long expected_gcd = gcd(integer1, integer2);
        REQUIRE(gcd(big_int1, big_int2)     == expected_gcd);
        REQUIRE(gcd(big_int1, integer2)     == expected_gcd);
        REQUIRE(gcd(big_int1, integer2_str) == expected_gcd);
        REQUIRE(gcd(big_int2,     big_int1) == expected_gcd);
        REQUIRE(gcd(integer2,     big_int1) == expected_gcd);
        REQUIRE(gcd(integer2_str, big_int1) == expected_gcd);
    }
}

TEST_CASE("Base cases for gcd()", "[functions][math][gcd]") {
    BigInt num = 123456789;
    REQUIRE(gcd(num, 0)  == num);
    REQUIRE(gcd(0, -num) == num);

    num = "-5912497820419707218240478194215164153";
    REQUIRE(gcd(num, 0)  == -num);
    REQUIRE(gcd(0, -num) == -num);
}

TEST_CASE("gcd() of big integers", "[functions][math][gcd][big]") {
    BigInt num1, num2;
    num1 = "-28701459619301513978950179078087383496799625608342360911660546962"
        "6226480898832387914378647227381298172400875321359626526";
    num2 = "259676874116728507995615797792043346565959939008390306340060244299"
        "957115837743525129541487196215617038210022066763254690980408296383116"
        "7438735691920771807553565900345087703773104";
    REQUIRE(gcd(num1, num2) == "2870145961930151397895017907808738349679962560"
        "834236091166054696262264808988323879143786472273812981724008753213596"
        "26526");

    num1 = "502709688287865084979589372814644735042152904730080078588488501749"
        "304853656848471698577996697331106182773782819152187924589506119423139"
        "3449809274726857526593076";
    num2 = "229801173305277725653531537012213553527219194341261839531874161152"
        "120471652370285152798196993513652596100648576424699198031891109543456"
        "40291279915526420792768837307589165628581578497517531497793276";
    REQUIRE(gcd(num1, num2) == "5027096882878650849795893728146447350421529047"
        "300800785884885017493048536568484716985779966973311061827737828191521"
        "879245895061194231393449809274726857526593076");

    num1 = "179808363116887720418632899034744992715140532806272754227625836421"
        "314089790834938436981704176026712384458366664389143163105529357675898"
        "863842312404914634799999961195725750525719410167387438425426347823552"
        "0875839344564111160862825105725176379138229960";
    num2 = "360678681586952249424916997435717051409065719201628568070971812924"
        "175497184487423342549160121583044936658711604011498293651939726933392"
        "310411364541796522417366059941501171344834807935292044485515752515846"
        "5050742997335518052240435760284538105240916712";
    REQUIRE(gcd(num1, num2) == "2967318005406102180152352893326198207229760677"
        "892175934946549883420397056138122377874078159295664869224987233341800"
        "165838235976741016342171914264316392");
}


long long lcm(long long a, long long b) {
    if (a == 0 or b == 0)
        return 0;
    return llabs(a * b) / gcd(a, b);
}

TEST_CASE("Randomised test for lcm()", "[functions][math][lcm][random]") {
    std::random_device generator;
    // uniform distribution of numbers from -3037000499 to 3037000499:
    std::uniform_int_distribution<long long> distribution((-FLOOR_SQRT_LLONG_MAX),
            (FLOOR_SQRT_LLONG_MAX));
    for (size_t i = 0; i < 100; i++) {
        long long integer1 = distribution(generator);
        long long integer2 = distribution(generator);


        BigInt big_int1 = integer1;
        BigInt big_int2 = integer2;
        std::string integer2_str = std::to_string(integer2);

        long long expected_lcm = lcm(integer1, integer2);
        REQUIRE(lcm(big_int1, big_int2)     == expected_lcm);
        REQUIRE(lcm(big_int1, integer2)     == expected_lcm);
        REQUIRE(lcm(big_int1, integer2_str) == expected_lcm);
        REQUIRE(lcm(big_int2,     big_int1) == expected_lcm);
        REQUIRE(lcm(integer2,     big_int1) == expected_lcm);
        REQUIRE(lcm(integer2_str, big_int1) == expected_lcm);
    }
}

TEST_CASE("Base cases for lcm()", "[functions][math][lcm]") {
    BigInt num = -9876543210;
    REQUIRE(lcm(num, 0)  == 0);
    REQUIRE(lcm(0, -num) == 0);

    num = "219019024102157019457158092713173121573";
    REQUIRE(lcm(num, 0)  == 0);
    REQUIRE(lcm(0, -num) == 0);
}

TEST_CASE("lcm()of big integers", "[functions][math][lcm][big]") {
    BigInt num1, num2;
    num1 = "-633293162545235516827204921608484039876880488546867238715155";
    num2 = "751467462681527802564845512694233047131278025010963143942272";
    REQUIRE(lcm(num1, num2) == "3660763123010988395932260487955625105886372221"
        "087113492935131297854937091253061105429105293659470657022754363775165"
        "6320");

    num1 = "431725782679516687812397269094148164228788688988330296960502266891"
        "277126317871224101300816470466899";
    num2 = "210204267611934443161921831201103550498213144947220752751829704138"
        "0385675074011446417186911955170127";
    REQUIRE(lcm(num1, num2) == "9075060195733697769850772263661839623306634656"
        "150065383714705331906315350838857000789836809159490190572469790732585"
        "553705831078778137138399554273866158564526814198650782346897029240548"
        "58548667126173");

    num1 = "486478183750203693027954972176960357768543354407814554669357573593"
        "9153465244560450505234315632071983";
    num2 = "170392478191571803530259651455950875922139049689136212457315013318"
        "8135167718854241496296593603612002";
    REQUIRE(lcm(num1, num2) == "8289222331533204329893614622858422873253500551"
        "773165023583543979273894307090377362282997909371974857157338418233214"
        "533220692127153044311875258011747917053108027629278373174251200266431"
        "428784066739966");
}
