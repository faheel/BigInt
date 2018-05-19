#include <random>

#include "constructors/constructors.hpp"
#include "operators/assignment.hpp"
#include "operators/io_stream.hpp"
#include "operators/relational.hpp"
#include "operators/binary_arithmetic.hpp"

#include "third_party/catch.hpp"


TEST_CASE("Binary arithmetic operations on BigInts with integers, strings and BigInts",
        "[operators][binary-arithmetic][addition][subtraction][multiplication]"
        "[division][modulo][integer][string][BigInt]") {
    std::random_device generator;
    // uniform distribution of numbers from -3037000499 to 3037000499:
    std::uniform_int_distribution<long long> distribution((-FLOOR_SQRT_LLONG_MAX),
            (FLOOR_SQRT_LLONG_MAX));
    for (size_t i = 0; i < 20; i++) {
        long long integer1 = distribution(generator);
        long long integer2 = distribution(generator);
        if (integer1 == 0 or integer2 == 0) {   // prevent division by zero
            i--;
            continue;
        }

        BigInt big_int1 = integer1;
        BigInt big_int2 = integer2;
        std::string integer2_str = std::to_string(integer2);

        // addition:
        long long sum = integer1 + integer2;
        REQUIRE(big_int1 + big_int2     == sum);
        REQUIRE(big_int1 + integer2     == sum);
        REQUIRE(big_int1 + integer2_str == sum);
        REQUIRE(big_int2     + big_int1 == sum);
        REQUIRE(integer2     + big_int1 == sum);
        REQUIRE(integer2_str + big_int1 == sum);

        // subtraction:
        long long difference = integer1 - integer2;
        REQUIRE(big_int1 - big_int2     == difference);
        REQUIRE(big_int1 - integer2     == difference);
        REQUIRE(big_int1 - integer2_str == difference);
        REQUIRE(big_int2     - big_int1 == -difference);
        REQUIRE(integer2     - big_int1 == -difference);
        REQUIRE(integer2_str - big_int1 == -difference);

        // multiplication:
        long long product = integer1 * integer2;
        REQUIRE(big_int1 * big_int2     == product);
        REQUIRE(big_int1 * integer2     == product);
        REQUIRE(big_int1 * integer2_str == product);
        REQUIRE(big_int2     * big_int1 == product);
        REQUIRE(integer2     * big_int1 == product);
        REQUIRE(integer2_str * big_int1 == product);

        // division:
        long long quotient = integer1 / integer2;
        long long quotient_reciprocal = integer2 / integer1;
        REQUIRE(big_int1 / big_int2     == quotient);
        REQUIRE(big_int1 / integer2     == quotient);
        REQUIRE(big_int1 / integer2_str == quotient);
        REQUIRE(big_int2     / big_int1 == quotient_reciprocal);
        REQUIRE(integer2     / big_int1 == quotient_reciprocal);
        REQUIRE(integer2_str / big_int1 == quotient_reciprocal);

        // modulo:
        long long remainder = integer1 % integer2;
        long long remainder_reciprocal = integer2 % integer1;
        REQUIRE(big_int1 % big_int2     == remainder);
        REQUIRE(big_int1 % integer2     == remainder);
        REQUIRE(big_int1 % integer2_str == remainder);
        REQUIRE(big_int2     % big_int1 == remainder_reciprocal);
        REQUIRE(integer2     % big_int1 == remainder_reciprocal);
        REQUIRE(integer2_str % big_int1 == remainder_reciprocal);
    }
}

TEST_CASE("Binary arithmetic operations with zeroes",
        "[operators][binary-arithmetic][addition][subtraction][multiplication]"
        "[division][modulo]") {
    BigInt num;
    num = "1234567890123456789012345678901234567890";

    REQUIRE(num + 0 == num);
    REQUIRE(num - 0 == num);
    REQUIRE(num * 0 == 0);

    try {
        BigInt undefined = num / 0;
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Attempted division by zero"));
    }
    try {
        BigInt undefined = num % 0;
    }
    catch (std::logic_error &e) {
        CHECK(e.what() == std::string("Attempted division by zero"));
    }

    REQUIRE(0 + num ==  num);
    REQUIRE(0 - num == -num);
    REQUIRE(0 * num == 0);
    REQUIRE(0 / num == 0);
    REQUIRE(0 % num == 0);
}

TEST_CASE("Chaining addition and subtraction",
        "[binary-arithmetic][operators][addition][subtraction]") {
    BigInt num1 = 1234;
    BigInt num2 = 56789;
    BigInt num3 = 101112;
    BigInt num4 = 13141516;
    REQUIRE(num1 + num2 + num3 + num4 == 13300651);
    REQUIRE(num1 - num2 + num3 + num4 == 13187073);
    REQUIRE(num1 + num2 - num3 + num4 == 13098427);
    REQUIRE(num1 + num2 + num3 - num4 == -12982381);
    REQUIRE(num1 - num2 - num3 + num4 == 12984849);
    REQUIRE(num1 - num2 + num3 - num4 == -13095959);
    REQUIRE(num1 + num2 - num3 - num4 == -13184605);
    REQUIRE(num1 - num2 - num3 - num4 == -13298183);
}

TEST_CASE("Chaining multiplication, division and modulo",
        "[binary-arithmetic][operators][multiplication][division][modulo]") {
    BigInt num1 = 313233343536373839;
    BigInt num2 = 212223242526272829;
    BigInt num3 = 111213141516171819;
    BigInt num4 = 12345678910;
    REQUIRE(num1 * num2 / num3 % num4 == 9021418300);
    REQUIRE(num1 * num2 % num3 / num4 == 6392448);
    REQUIRE(num1 / num2 * num3 % num4 == 6635659579);
    REQUIRE(num1 / num2 % num3 * num4 == 12345678910);
    REQUIRE(num1 % num2 * num3 / num4 == "909925710857417206643517");
    REQUIRE(num1 % num2 / num3 * num4 == 0);
}

TEST_CASE("Addition of big numbers",
        "[binary-arithmetic][operators][addition][big]") {
    BigInt num1, num2;
    num1 = "964793941351798875130890128898086485681241334814868066116469822595"
           "687598448053045508928021048387109439448430241206886222949385913536"
           "17836411623804682393334501579397617644828334316728238955353058394264";
    num2 = "542060529704217132357214772959828385120983424339263541090375634996"
           "368065850294867611447397165152437998796443501783597014569840671683"
           "13210331303669787440432347511637996556242776045622241233979589718916";
    REQUIRE(num1 + num2 == "15068544710560160074881049018579148708022247591541"
            "31607206845457592055664298347913120375418213539547438244873742990"
            "48323751922658521931046742927474469833766849091035614201071110362"
            "350480189332648113180");

    num1 = "-19456862453160453307638071783433388649631926064367472120354136295"
           "908610671862754051755238831363430525061125138089083649263206899106"
           "180343851589754547911836910916517013121829987691413708752682939530093";
    num2 = "816553076977620349766958416466042124954414412870431261355772588173"
           "273756816453377871361812881641294479548961786166170884010949495342"
           "27956257833623792756494659469534082561332606937935191051654689548416";
    REQUIRE(num1 + num2 == "62198445244601581669057769863170823845809515222675"
            "65401522312252141876500978258373538094245680069892289377104052753"
            "34391378880504280476124062438692448446577485530170694395026192465"
            "21482298971750018323");

    num1 = "239051672644169719606760847726448849722952349353674737803305086175"
           "964897566266679588060951437665097321115985305673099530769568871522"
           "45499107716567135414777307777041355408432721268223982670393229830408";
    num2 = "-45388635689554372889456021208799010297399750799135284700297465410"
           "290594446637518031367847208953611686547054464297776583106699748315"
           "71906644184297446268805816895836929754710634789080915280425559423001";
    REQUIRE(num1 + num2 == "19366303695461534671730482651764983942555259855453"
            "94531030076207656743031196291615566931042287114856345689308413753"
            "22947662869123206735924635322696891459714908812044256537220864791"
            "43067389967670407407");

    std::string sum;
    num1 = big_pow10(1525);
    num2 = big_pow10(2750);
    sum = "1" + std::string(2750 - 1525 - 1, '0') + "1" + std::string(1525, '0');
    REQUIRE(num1 + num2 == sum);

    num1 = big_pow10(3875);
    num2 = -big_pow10(5490);
    sum = "-" + std::string(5490 - 3875, '9') + std::string(3875, '0');
    REQUIRE(num1 + num2 == sum);

    num1 = big_pow10(19876);
    num2 = big_pow10(23450);
    sum = "1" + std::string(23450 - 19876 - 1, '0') + "1" + std::string(19876, '0');
    REQUIRE(num1 + num2 == sum);
}

TEST_CASE("Subtraction of big numbers",
        "[binary-arithmetic][operators][subtraction][big]") {
    BigInt num1, num2;
    num1 = "244519519883208981610410491992186770044882615922116562728872847144"
           "421092065072619855932223524830025832896873758619497075789940851207"
           "16036623521081847217851760412478092335656686950878812602818804060088";
    num2 = "-94425733811917851828605532625703702955076512086024371088350998261"
           "196757834829702575354045148220569953447106949397940559706260326388"
           "28634363448939208619936099903329996345089935704304349196301998955360";
    REQUIRE(num1 - num2 == "33894525369512683343901602461789047299995912800814"
            "09338172238454056178498999023224312862686730505957863439807080174"
            "37635496201177595446709869700210558377878603158080886807466226551"
            "83161799120803015448");

    num1 = "-68985388257152076898307722398568069114569275150745660636500453122"
           "361335250374573735886985878878256091550832525534234783139806339978"
           "04531841900565455099200079685136917576702910555227461601790724376924";
    num2 = "727483877648813365652533679594255899405397184767522058008426131998"
           "131529490549312516017332620262440606302137189946954415157145256899"
           "53212281719565428986155762468758034363469065219343576930733687283864";
    REQUIRE(num1 - num2 == "-7964692659059654425508414019928239685199664599182"
            "67718644926585120492864740923886251904318499140696697852969715481"
            "18919829695159687757744123620130884085355842153894951940171975774"
            "571038532524411660788");

    num1 = "925303738374648618488768260990584709987661046412988919780698877679"
           "650011360190156923243086758248351549060110046601233139482977571723"
           "68389150744548489610998029282638268114361253166438240576351224508584";
    num2 = "523739575704971221852123690170162065549469315720636849353841858576"
           "794958912896691529594741418267238468975328418156471008089785554092"
           "454742205154244706320735384145817395506750071592361784501457672552";
    REQUIRE(num1 - num2 == "92006634261759890627024702408888308933216635325578"
            "25512871604590938820617710611900079471393440656791643703567624196"
            "68429402079716182759344085393942449046772938984924507188545030948"
            "45878791849766836032");

    std::string difference;
    num1 = big_pow10(3126);
    num2 = big_pow10(2097);
    difference = std::string(3126 - 2097, '9') + std::string(2097, '0');
    REQUIRE(num1 - num2 == difference);

    num1 = big_pow10(3875);
    num2 = -big_pow10(5490);
    difference = "1" + std::string(5490 - 3875 - 1, '0') + "1" + std::string(3875, '0');
    REQUIRE(num1 - num2 == difference);

    num1 = big_pow10(35088);
    num2 = big_pow10(27149);
    difference = std::string(35088 - 27149, '9') + std::string(27149, '0');
    REQUIRE(num1 - num2 == difference);
}

TEST_CASE("Multiplication of big numbers",
        "[binary-arithmetic][operators][multiplication][big]") {
    BigInt num1, num2;
    num1 = "1234567890";
    num2 = "12345678901234567890";
    REQUIRE(num1 * num2 == "15241578751714678875019052100");

    num1 = "74795969103554554996215276693934490847811844274620";
    num2 = "-52918576235658446609301827261047318817814919806509";
    REQUIRE(num1 * num2 == "-39580961931264054802943979852752588263328417515871"
        "01538786510224257493862421103501026851769859501580");

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "4229896130736";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986"
        "9764487550589";
    REQUIRE(num1 * num2 == "688329440923680539900273976992795654211511681990024"
        "3223280952847744060245431221201608457153558098391226973463787572086498"
        "8286684146085609255199499546372688486729372202884271671750355256222081"
        "1343929322816987582816790738952977665859931342689201004021415981394352"
        "574892370071759247880576536253157803504");

    num1 = big_pow10(1525);
    num2 = big_pow10(2750);
    REQUIRE(num1 * num2 == big_pow10(4275));

    num1 = big_pow10(3875);
    num2 = -big_pow10(5490);
    REQUIRE(num1 * num2 == -big_pow10(9365));

    num1 = big_pow10(19876);
    num2 = big_pow10(23450);
    REQUIRE(num1 * num2 == big_pow10(43326));

    num1 = big_pow10(19876) + 1;
    num2 = big_pow10(23450);
    REQUIRE(num1 * num2 == big_pow10(43326) + big_pow10(23450));
}

TEST_CASE("Base cases for division", "[binary-arithmetic][operators][division]") {
    BigInt num;
    num = "1234567890123456789012345678901234567890";

    REQUIRE(num /  1 ==  num);
    REQUIRE(num / -1 == -num);

    REQUIRE((num - 1) / num == 0);
}

TEST_CASE("Division of big numbers",
        "[binary-arithmetic][operators][division][big]") {
    BigInt num1, num2;
    num1 = "12345678901234567890";
    num2 = "1234567890";
    REQUIRE(num1 / num2 == 10000000001);

    num1 = "74795969103554554996215276693934490847811844274620";
    num2 = "-5291857623565844660930182726104731881781491980";
    REQUIRE(num1 / num2 == -14134);

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "42298961307365134004615";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986"
        "976448753";
    REQUIRE(num1 / num2 == "133402211172555");

    num1 = "-920132912302829612061902393145744233945758297736906406054053889535"
        "6968429805690068413076628064294801864511568551589205855316992620853084"
        "3219577396774861536705894326785721164938367932913682323736670444";
    num2 = "-126173815845557317670134103088446550114061753703252550511788939308"
        "82979573617430830373800";
    REQUIRE(num1 / num2 == "729258211092795635494143745485389681543083349270759"
        "3708106029725015022394056069241322168656324094196515329458910");

    num1 = big_pow10(456);
    num2 = big_pow10(123);
    REQUIRE(num1 / num2 == big_pow10(333));

    num1 = big_pow10(2749);
    num2 = big_pow10(1523);
    REQUIRE(num1 / num2 == big_pow10(1226));

    num1 = -big_pow10(5483);
    num2 = big_pow10(3877);
    REQUIRE(num1 / num2 == -big_pow10(1606));

    num1 = big_pow10(23459);
    num2 = big_pow10(19867);
    REQUIRE(num1 / num2 == big_pow10(3592));
}

TEST_CASE("Base cases for modulo", "[binary-arithmetic][operators][modulo]") {
    BigInt num;
    num = "1234567890123456789012345678901234567890";

    REQUIRE(num %  1 == 0);
    REQUIRE(num % -1 == 0);

    REQUIRE(num %  num == 0);
    REQUIRE(num % -num == 0);
}

TEST_CASE("Modulo of big numbers",
        "[binary-arithmetic][operators][modulo][big]") {
    BigInt num1, num2;
    num1 = "12345678909876543210123456789";
    num2 = 1234567890;
    REQUIRE(num1 % num2 == 819);

    num1 = "-74795969103554554996215276693934490847811844274620";
    num2 = "529185762356584466093018272610473188178149";
    REQUIRE(num1 % num2 == "-404625987744468732097714762347932921438432");

    num1 = "9582518950379800614306095260421646856475999938972041161410754824718"
        "8530515989621711174263184271175858137696144827610415473041959151743248"
        "42298961307365134004615";
    num2 = "7183178499181562107254471437293951674461271038850005413302515662375"
        "5697355361810132505715688137025455771038053164648324034388264089738986";
    REQUIRE(num1 % num2 == "502008140524007203128630082431770583307845442935791"
        "9728555544083411210356832664053040147221561393576626728850496195492998"
        "0314390096754463");

    num1 = "920132912302829612061902393145744233945758297736906406054053889535"
        "6968429805690068413076628064294801864511568551589205855316992620853084"
        "3219577396774861536705894326785721164938367932913682323736670444";
    num2 = "-126173815845557317670134103088446550114061753703252550511788939308"
        "82979573617430830373800";
    REQUIRE(num1 % num2 == "103737999458960727172146109955280604488347153612922"
        "63695257182569105701287999976696112444");

    num1 = big_pow10(456);
    num2 = big_pow10(123);
    REQUIRE(num1 % num2 == 0);

    num1 = -big_pow10(6789);
    num2 = big_pow10(2345);
    REQUIRE(num1 % num2 == 0);

    num1 = big_pow10(23450);
    num2 = big_pow10(19876);
    REQUIRE(num1 % num2 == 0);
}
