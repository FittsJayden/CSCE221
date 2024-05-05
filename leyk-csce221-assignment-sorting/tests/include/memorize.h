#pragma once

#include <array>

struct memorize {
    static constexpr double bubble_error_multiplier{ 0.15 };

    static constexpr double insertion_error_multiplier{ 0.015 };

    static constexpr double selection_error_multiplier{ 0.05 };

    [[nodiscard]] static double bubble_error(size_t size) {
        return bubble_comparisons[size] * bubble_error_multiplier;
    }

    [[nodiscard]] static double insertion_error(size_t size) {
        return insertion_comparisons[size] * insertion_error_multiplier;
    }

    [[nodiscard]] static double selection_error(size_t size) {
        return selection_comparisons[size] * selection_error_multiplier;
    }

    static const std::array<double, 1000> bubble_comparisons;

    static const std::array<double, 1000> insertion_comparisons;

    static const std::array<double, 1000> selection_comparisons;
};

inline const std::array<double, 1000> memorize::bubble_comparisons {
    0, 0, 1, 3, 6, 9.5, 15, 21, 26.5, 35.5, 45, 50, 64.5, 73, 89.5, 103.5, 112.5, 134.5, 151.5, 163.5, 179.5, 208.5, 230.5, 245.5, 275.5, 298.5, 286, 328.5, 377.5, 395.5, 430, 460, 494.5, 520.5, 561, 581, 619.5, 638.5, 700, 713.5, 766, 787, 847, 901.5, 907, 987, 1033.5, 1078, 1110, 1168.5, 1223.5, 1270, 1318.5, 1367.5, 1423.5, 1446, 1463.5, 1596, 1620, 1697, 1767, 1828.5, 1877, 1876.5, 1993.5, 2057.5, 2131, 2158.5, 2264, 2269.5, 2414.5, 2482, 2523, 2589, 2696, 2752.5, 2850, 2921, 3000, 3053.5, 3127, 3229.5, 3216, 3380.5, 3453, 3568.5, 3616, 3713.5, 3789, 3902, 3987, 4062, 4184.5, 4264, 4357, 4447, 4410, 4617, 4693, 4833, 4873.5, 5039.5, 5128.5, 5245.5, 5323, 5407.5, 5488.5, 5668, 5701.5, 5858.5, 5890, 6077.5, 6121, 6314, 6430.5, 6537, 6624.5, 6718, 6787.5, 7016, 7112.5, 7242, 7370.5, 7443, 7598.5, 7745, 7822.5, 7924.5, 8089, 8242, 8377.5, 8447, 8600.5, 8545.5, 8903.5, 9027, 9179.5, 9230.5, 9393, 9568.5, 9644.5, 9831, 9916, 9990.5, 10285.5, 10264.5, 10525, 10604.5, 10876.5, 11021, 11037, 11220, 11313.5, 11625, 11753.5, 11912.5, 12062.5, 12130.5, 12370, 12411, 12692.5, 12878.5, 12973, 13180.5, 13358.5, 13477.5, 13690, 13756, 14005.5, 14191, 14362, 14533.5, 14703, 14630, 15037, 15062.5, 15323.5, 15523.5, 15693, 15871, 16092, 16230, 16448.5, 16642.5, 16759.5, 16915, 17159.5, 17383.5, 17545, 17752, 17828.5, 18077, 18209.5, 18517.5, 18626, 18847, 19082.5, 19229.5, 19270.5, 19453, 19667.5, 19911, 20233, 20495.5, 20556, 20871, 21062.5, 21288, 21514, 21659.5, 21885, 22078.5, 21802, 22576.5, 22675.5, 22945, 23104.5, 23247, 23593, 23811, 24082.5, 24296, 24471, 24520.5, 24890.5, 24810, 25236, 25646, 25689, 25917, 26275, 26460, 26658, 26923, 27111, 27390, 27719.5, 27948, 28157.5, 28402, 28672.5, 28867.5, 28913, 29308, 29635.5, 29714.5, 30134.5, 30335.5, 30605.5, 30713.5, 30975, 31248.5, 31393.5, 31689, 31955.5, 32384.5, 32288.5, 32819.5, 33135, 33358.5, 33602, 33877.5, 33839.5, 34425.5, 34688.5, 34980, 35107, 35500.5, 35388, 35960.5, 36313.5, 36337, 36810.5, 37068, 37274.5, 37512.5, 37635, 38203.5, 38443, 38592, 38708.5, 39301, 39561, 39850.5, 40109.5, 40320, 40365, 40878.5, 40995, 41440.5, 41852.5, 41977.5, 42391, 42710, 42944.5, 42702, 43510, 43923, 44214, 44512, 44845, 45117, 45356, 45693, 45775.5, 46307.5, 46515, 46932, 47115.5, 47383, 47877, 48145, 48477, 48789, 48978.5, 49455, 49418.5, 49959.5, 50287.5, 50693.5, 51032.5, 51184.5, 51663, 51989, 51895.5, 52545, 52915, 53293.5, 53595, 53806, 54169.5, 54601, 54860.5, 55151.5, 55221, 55931, 56277, 56577, 56925.5, 57186, 57597, 57752.5, 58243, 58515, 58968.5, 59294.5, 59682, 59963, 60202.5, 60718.5, 60899.5, 61287, 61638, 61738, 62318.5, 62554.5, 63151, 63343, 63385.5, 64085.5, 64617, 64853.5, 65203, 65675.5, 66033, 66377.5, 66727, 66863.5, 67527.5, 67663.5, 68188.5, 68446, 68920.5, 69189, 69665.5, 69962.5, 70384.5, 70578.5, 70938, 71493, 71847.5, 72263.5, 72738, 73100.5, 73347, 73656, 73642, 74515.5, 74132.5, 75389.5, 75360, 76234.5, 76590.5, 76960, 77173, 77747, 78094.5, 78373.5, 78865, 78658.5, 79754.5, 80172.5, 80533, 80985, 81073, 81420, 82052.5, 81378.5, 82912.5, 83286, 83729.5, 83667, 84314.5, 84860.5, 85353, 85755, 86281, 86586, 86964, 87485.5, 87913.5, 88020, 88379.5, 89126.5, 89599.5, 90032, 90398.5, 90670.5, 91080.5, 91690.5, 92108.5, 92597, 92023.5, 93505.5, 93373, 93117, 94827, 94951, 95702.5, 96133.5, 96569.5, 96870, 97180.5, 97551.5, 98196, 98776, 99227.5, 99565.5, 100052, 100450, 100992, 101442, 101918, 102350, 102736, 103278, 103222, 103656, 104338, 104740, 105484, 105984, 106158, 106868, 107168, 107742, 108182, 108496, 109060, 109713, 109934, 110667, 111088, 111533, 112062, 112260, 113040, 113440, 113840, 114436, 114662, 115302, 115910, 116398, 116770, 117254, 117841, 117846, 118782, 118798, 119541, 120218, 120681, 120615, 121158, 121814, 122634, 122846, 123010, 124206, 124698, 125222, 125733, 126078, 126567, 127155, 127201, 127990, 128732, 129278, 129514, 129328, 130518, 131252, 131043, 131860, 132555, 133376, 133552, 134258, 134926, 135228, 135778, 135733, 136823, 137434, 137886, 138556, 139089, 139628, 139937, 140220, 139744, 141683, 142272, 142281, 143358, 143778, 144376, 144853, 145484, 146052, 146593, 146743, 147432, 147442, 148596, 148814, 149773, 150366, 150936, 151486, 151960, 152380, 152708, 153620, 154272, 154657, 155343, 155758, 156302, 156800, 157438, 157939, 158738, 158900, 159378, 160311, 160796, 161470, 161932, 162518, 163074, 163689, 164356, 164635, 165411, 166000, 166742, 167246, 167458, 168340, 168576, 169464, 170234, 170670, 171310, 171788, 172452, 173127, 173750, 173305, 174897, 174520, 176006, 176151, 177250, 177744, 178458, 179098, 179678, 180286, 180604, 181008, 181000, 182098, 182751, 183853, 184366, 185103, 185650, 186091, 186816, 187416, 188106, 187454, 189325, 189584, 190464, 191248, 191752, 192442, 193071, 193668, 194128, 194202, 194452, 195800, 196752, 197484, 198108, 198292, 198986, 199810, 200643, 200864, 201814, 202514, 202514, 203802, 202978, 204730, 205572, 205740, 206814, 207078, 207230, 208948, 209330, 210100, 210830, 211480, 212110, 212802, 213342, 214010, 214772, 214780, 216076, 216673, 217384, 217968, 217718, 219400, 219170, 220618, 221295, 221474, 222710, 223076, 223965, 224658, 225141, 225952, 226756, 227024, 228104, 228676, 229255, 229900, 230671, 231501, 231633, 231988, 233306, 234242, 234584, 235424, 236223, 236784, 237334, 237878, 238546, 239692, 240333, 238740, 241684, 241944, 243126, 243846, 244545, 244580, 246050, 246489, 247330, 247687, 248727, 248594, 249945, 250491, 250655, 252216, 252954, 253564, 254024, 255216, 255690, 256653, 257376, 258110, 258560, 259384, 260154, 260530, 261588, 262404, 263060, 263878, 264040, 265058, 265970, 266652, 267357, 268075, 268601, 269640, 269764, 270652, 271803, 272638, 273335, 274124, 274540, 275568, 276344, 276730, 277170, 278350, 279130, 280058, 280870, 281436, 281687, 283123, 283364, 283837, 285322, 285673, 286570, 287654, 288418, 288977, 289791, 290698, 291328, 292012, 292918, 293410, 294452, 294926, 296012, 296554, 296943, 297905, 299091, 299907, 300182, 301273, 302242, 303030, 303684, 304474, 305138, 306068, 306936, 307310, 308452, 308818, 309992, 310728, 311570, 311590, 313047, 313933, 314540, 315488, 316272, 316543, 317508, 318086, 319474, 320250, 320791, 321486, 322738, 323472, 323276, 325071, 325878, 326010, 327470, 327712, 329140, 329648, 330884, 331254, 332302, 333147, 333950, 334201, 334875, 336577, 336890, 338126, 338191, 339184, 340620, 341474, 341715, 343178, 343471, 344826, 345223, 345730, 346990, 348142, 348944, 349514, 350455, 351090, 351404, 352047, 354001, 354493, 355514, 356200, 357428, 358000, 359012, 359954, 360820, 361324, 362388, 363228, 363542, 364012, 365607, 365911, 367585, 368497, 369352, 369950, 369704, 371764, 372518, 373530, 374342, 374798, 376264, 377020, 377326, 378867, 379423, 379588, 381268, 382336, 382755, 383894, 384706, 385450, 385410, 387554, 388170, 389088, 390247, 390837, 391774, 392660, 392882, 394600, 395110, 396247, 397270, 398275, 398923, 399180, 400590, 401638, 401926, 402766, 403125, 404535, 405878, 407090, 407766, 409057, 409860, 410870, 411616, 412406, 413457, 414288, 415227, 416080, 417181, 417992, 418944, 419634, 419926, 421132, 422551, 422971, 424248, 425132, 426178, 426524, 427032, 428346, 429272, 431028, 431890, 432582, 432774, 434214, 435238, 436348, 437282, 438488, 439400, 440338, 439670, 440956, 442038, 444135, 444024, 445776, 446688, 447667, 448810, 449688, 450670, 451036, 452306, 452858, 453636, 455512, 455351, 456808, 457605, 458844, 460234, 460910, 462196, 462955, 463756, 465097, 466094, 466946, 467143, 468957, 469448, 470654, 471342, 472314, 473420, 474650, 475695, 474862, 477456, 477070, 479072, 480472, 481008, 482436, 483541, 484388, 484466, 485736, 487263, 488440, 489145, 490328, 490496, 492076, 492933, 493974, 495442, 496460, 496078, 498416
};

inline const std::array<double, 1000> memorize::insertion_comparisons {
    0, 0, 1, 2, 5, 7, 11, 21, 16, 25, 41, 35, 50, 47, 55, 64, 76, 90, 83, 80, 113, 134, 128, 141, 172, 174, 143, 151, 242, 201, 243, 280, 255, 343, 343, 360, 336, 325, 356, 363, 405, 430, 512, 487, 480, 574, 611, 547, 602, 567, 686, 768, 811, 679, 807, 724, 880, 788, 865, 911, 884, 1042, 918, 964, 1061, 1201, 1107, 1089, 1021, 1267, 1192, 1289, 1511, 1401, 1607, 1358, 1674, 1521, 1588, 1837, 1698, 1725, 1452, 1762, 1774, 1866, 1886, 1932, 2050, 2125, 2028, 2092, 2369, 2017, 2484, 2437, 2175, 2165, 2303, 2711, 2513, 2541, 2848, 2397, 3216, 2843, 3059, 2951, 2835, 3115, 2999, 2846, 3240, 3188, 3353, 3313, 3678, 3513, 3018, 3442, 3699, 3278, 3545, 3840, 4064, 4133, 4040, 3649, 4256, 4561, 4436, 4457, 3962, 4432, 4382, 5046, 4567, 5058, 4498, 5132, 4820, 4775, 4673, 4896, 5186, 5002, 5356, 5237, 5882, 5343, 5101, 5388, 5845, 5958, 5867, 6313, 6358, 6164, 6468, 6528, 6439, 6465, 6606, 6922, 6978, 7373, 6891, 6728, 6793, 7265, 7794, 6996, 7848, 7455, 7772, 8349, 7586, 8301, 7516, 8094, 7085, 9021, 9441, 8735, 8423, 8772, 9454, 9042, 9634, 8740, 9293, 9688, 8948, 9965, 10018, 10200, 9658, 10885, 10731, 10249, 9563, 10195, 11194, 9797, 10291, 10593, 10924, 11342, 10777, 10771, 10659, 11336, 11495, 12053, 12002, 11989, 12179, 11426, 11697, 12126, 12239, 12655, 12251, 11254, 12713, 12528, 12841, 13246, 12789, 13301, 14651, 13700, 13473, 13759, 13996, 14096, 14300, 15058, 14050, 14869, 14606, 15869, 13771, 16173, 14675, 16062, 15217, 16195, 15892, 16254, 15417, 15444, 16448, 15875, 16074, 16834, 15955, 16807, 16142, 16123, 18561, 17027, 17612, 17155, 17325, 17372, 17576, 18774, 17822, 19426, 19123, 19392, 17856, 19154, 19205, 19436, 19113, 19026, 18998, 20628, 18882, 20471, 20223, 21113, 20099, 20587, 20038, 19945, 20696, 22133, 19365, 21642, 22620, 20804, 22417, 23142, 22136, 23505, 21736, 23424, 24358, 24914, 24070, 21992, 22908, 22883, 24548, 24978, 23759, 24571, 24922, 24786, 26921, 25056, 23193, 25482, 26038, 27194, 27714, 26111, 26933, 25975, 25749, 26271, 27968, 26556, 26367, 26965, 27596, 26400, 28169, 26591, 26900, 29471, 28899, 28353, 28978, 28736, 28931, 28452, 29268, 30072, 28901, 30203, 29388, 29869, 29095, 29227, 29634, 30448, 31274, 31233, 32388, 31686, 30147, 31173, 30540, 31809, 30467, 33268, 34592, 32455, 33206, 32276, 34110, 32781, 35149, 34786, 35149, 34651, 33670, 33578, 35704, 35990, 33083, 33914, 35354, 36222, 36887, 36864, 35380, 37168, 37287, 33995, 38489, 37670, 38281, 37467, 37011, 37195, 38204, 38348, 38894, 41582, 41202, 40023, 39488, 40135, 41386, 39928, 39667, 39393, 42205, 39829, 40909, 40320, 41479, 42707, 44398, 41348, 42553, 40651, 41646, 44044, 43243, 43673, 42688, 44091, 45470, 45714, 44416, 44401, 45654, 46231, 43147, 46754, 45094, 44554, 45636, 46495, 45829, 46803, 48207, 47508, 46931, 47575, 47735, 48974, 47547, 48584, 47488, 49384, 51375, 50568, 48608, 50840, 49388, 49196, 51155, 50680, 50072, 49938, 51600, 53968, 53433, 52795, 52423, 51468, 52536, 53286, 53086, 55163, 54921, 52203, 53646, 54302, 56817, 52151, 57019, 55117, 52986, 57248, 54804, 60444, 59408, 54026, 58657, 57361, 58524, 57563, 55302, 58037, 59996, 60056, 58498, 61176, 61429, 58974, 61326, 60094, 59775, 61813, 63711, 58851, 58286, 62203, 60327, 60790, 61325, 63635, 60713, 62063, 63318, 66651, 61461, 63705, 62809, 62078, 62597, 64581, 67747, 65774, 67414, 66540, 67093, 68401, 69012, 65648, 65390, 67007, 68433, 70312, 66370, 67536, 73737, 69971, 70513, 71414, 72044, 70453, 66244, 71891, 69081, 72263, 71422, 70465, 74007, 71265, 77530, 71788, 73692, 79492, 71254, 70149, 71676, 75465, 76719, 73087, 77951, 73148, 74526, 77166, 77222, 75059, 77596, 77973, 79247, 79403, 80100, 74494, 77632, 80973, 76042, 78782, 76158, 83990, 79826, 79540, 79261, 80326, 81401, 79310, 82554, 82291, 89073, 81569, 80059, 83250, 78153, 86117, 86650, 87195, 88497, 85321, 90405, 84713, 84719, 85244, 86383, 91072, 85749, 90386, 88330, 91100, 85601, 85414, 90839, 87958, 89638, 89817, 90825, 95485, 94203, 96473, 92384, 95572, 95244, 93529, 92232, 91992, 92919, 91846, 94125, 92395, 95528, 93874, 98626, 96387, 95167, 96957, 98566, 95634, 98976, 97568, 100775, 97378, 101653, 102572, 102760, 100590, 95943, 102837, 98002, 105485, 106637, 101053, 99339, 103576, 104761, 97462, 101373, 104642, 109969, 107964, 101529, 105694, 105898, 105517, 110491, 103417, 101386, 108917, 107604, 106077, 109283, 109041, 111630, 105899, 107913, 108038, 109721, 105044, 112608, 110110, 108106, 111272, 112285, 109463, 113207, 112617, 111707, 115623, 111861, 114568, 110931, 112116, 116605, 117822, 119435, 115272, 111747, 117005, 117571, 120145, 118010, 119566, 120397, 120666, 115555, 119465, 120085, 124941, 121575, 123933, 122076, 115912, 122062, 121850, 124292, 122638, 127015, 124029, 127177, 122641, 129037, 128735, 126398, 121310, 119800, 125326, 122491, 123720, 128588, 130071, 128843, 124792, 125960, 135981, 129452, 129566, 130449, 121565, 131263, 137369, 137198, 131739, 133321, 137193, 138341, 133883, 135818, 131918, 137011, 139076, 136837, 131651, 132777, 133931, 138561, 133252, 138607, 139290, 138604, 140088, 137588, 138372, 144862, 141201, 139760, 143055, 141189, 139943, 139332, 143186, 137824, 148830, 145045, 139804, 143064, 137945, 147657, 140473, 148879, 153166, 148138, 143868, 144092, 145724, 149776, 150629, 146527, 149114, 150049, 147919, 153215, 149594, 154831, 150733, 153775, 154344, 153342, 156968, 152688, 159952, 150316, 154339, 149646, 158544, 154619, 153560, 161479, 157589, 160180, 161229, 154304, 155063, 157426, 155767, 163740, 158799, 162571, 164621, 156398, 168594, 158930, 150921, 162903, 164219, 166932, 163428, 163004, 162247, 159626, 169077, 165912, 168374, 163650, 167484, 160717, 159090, 168876, 168476, 164124, 172946, 170678, 169145, 170158, 174571, 170415, 172632, 170232, 177233, 166163, 173867, 168091, 171123, 180748, 174343, 178784, 172660, 176377, 180004, 181867, 173531, 181642, 181362, 182128, 181982, 177372, 176258, 174411, 176697, 189555, 189887, 178557, 191749, 179925, 183842, 180848, 181187, 187737, 194482, 181004, 189292, 187410, 184350, 191203, 194928, 195815, 193565, 188255, 197250, 191809, 179696, 189500, 195095, 190458, 193513, 192517, 193519, 193831, 193732, 187844, 191457, 199197, 198101, 192615, 191926, 199283, 201872, 207756, 208470, 201295, 200579, 204497, 193068, 201991, 207362, 201335, 198048, 202105, 208973, 211688, 208189, 211131, 207662, 200156, 202884, 210629, 214426, 206285, 208855, 208741, 215332, 212848, 218498, 211207, 205235, 211886, 217995, 213641, 214015, 205314, 205458, 223954, 223275, 214340, 212626, 211779, 214544, 217241, 212096, 218142, 219476, 221824, 227302, 222207, 221910, 230913, 216552, 224484, 227359, 218486, 228586, 220294, 227344, 225955, 223199, 223926, 225601, 224466, 223698, 220765, 226054, 228674, 230227, 225151, 234091, 233376, 223641, 234731, 240789, 228158, 228860, 240141, 237982, 232778, 241178, 231280, 235470, 238561, 227584, 228468, 226058, 239226, 238304, 239789, 235973, 240418, 238367, 246734, 241035, 240076, 239248, 235921, 239986, 233090, 248020, 240981, 243208, 244785, 241541, 246198, 245440, 252046, 246170, 245690, 242254, 247502, 250452
};

inline const std::array<double, 1000> memorize::selection_comparisons {
    0, 0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136, 153, 171, 190, 210, 231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666, 703, 741, 780, 820, 861, 903, 946, 990, 1035, 1081, 1128, 1176, 1225, 1275, 1326, 1378, 1431, 1485, 1540, 1596, 1653, 1711, 1770, 1830, 1891, 1953, 2016, 2080, 2145, 2211, 2278, 2346, 2415, 2485, 2556, 2628, 2701, 2775, 2850, 2926, 3003, 3081, 3160, 3240, 3321, 3403, 3486, 3570, 3655, 3741, 3828, 3916, 4005, 4095, 4186, 4278, 4371, 4465, 4560, 4656, 4753, 4851, 4950, 5050, 5151, 5253, 5356, 5460, 5565, 5671, 5778, 5886, 5995, 6105, 6216, 6328, 6441, 6555, 6670, 6786, 6903, 7021, 7140, 7260, 7381, 7503, 7626, 7750, 7875, 8001, 8128, 8256, 8385, 8515, 8646, 8778, 8911, 9045, 9180, 9316, 9453, 9591, 9730, 9870, 10011, 10153, 10296, 10440, 10585, 10731, 10878, 11026, 11175, 11325, 11476, 11628, 11781, 11935, 12090, 12246, 12403, 12561, 12720, 12880, 13041, 13203, 13366, 13530, 13695, 13861, 14028, 14196, 14365, 14535, 14706, 14878, 15051, 15225, 15400, 15576, 15753, 15931, 16110, 16290, 16471, 16653, 16836, 17020, 17205, 17391, 17578, 17766, 17955, 18145, 18336, 18528, 18721, 18915, 19110, 19306, 19503, 19701, 19900, 20100, 20301, 20503, 20706, 20910, 21115, 21321, 21528, 21736, 21945, 22155, 22366, 22578, 22791, 23005, 23220, 23436, 23653, 23871, 24090, 24310, 24531, 24753, 24976, 25200, 25425, 25651, 25878, 26106, 26335, 26565, 26796, 27028, 27261, 27495, 27730, 27966, 28203, 28441, 28680, 28920, 29161, 29403, 29646, 29890, 30135, 30381, 30628, 30876, 31125, 31375, 31626, 31878, 32131, 32385, 32640, 32896, 33153, 33411, 33670, 33930, 34191, 34453, 34716, 34980, 35245, 35511, 35778, 36046, 36315, 36585, 36856, 37128, 37401, 37675, 37950, 38226, 38503, 38781, 39060, 39340, 39621, 39903, 40186, 40470, 40755, 41041, 41328, 41616, 41905, 42195, 42486, 42778, 43071, 43365, 43660, 43956, 44253, 44551, 44850, 45150, 45451, 45753, 46056, 46360, 46665, 46971, 47278, 47586, 47895, 48205, 48516, 48828, 49141, 49455, 49770, 50086, 50403, 50721, 51040, 51360, 51681, 52003, 52326, 52650, 52975, 53301, 53628, 53956, 54285, 54615, 54946, 55278, 55611, 55945, 56280, 56616, 56953, 57291, 57630, 57970, 58311, 58653, 58996, 59340, 59685, 60031, 60378, 60726, 61075, 61425, 61776, 62128, 62481, 62835, 63190, 63546, 63903, 64261, 64620, 64980, 65341, 65703, 66066, 66430, 66795, 67161, 67528, 67896, 68265, 68635, 69006, 69378, 69751, 70125, 70500, 70876, 71253, 71631, 72010, 72390, 72771, 73153, 73536, 73920, 74305, 74691, 75078, 75466, 75855, 76245, 76636, 77028, 77421, 77815, 78210, 78606, 79003, 79401, 79800, 80200, 80601, 81003, 81406, 81810, 82215, 82621, 83028, 83436, 83845, 84255, 84666, 85078, 85491, 85905, 86320, 86736, 87153, 87571, 87990, 88410, 88831, 89253, 89676, 90100, 90525, 90951, 91378, 91806, 92235, 92665, 93096, 93528, 93961, 94395, 94830, 95266, 95703, 96141, 96580, 97020, 97461, 97903, 98346, 98790, 99235, 99681, 100128, 100576, 101025, 101475, 101926, 102378, 102831, 103285, 103740, 104196, 104653, 105111, 105570, 106030, 106491, 106953, 107416, 107880, 108345, 108811, 109278, 109746, 110215, 110685, 111156, 111628, 112101, 112575, 113050, 113526, 114003, 114481, 114960, 115440, 115921, 116403, 116886, 117370, 117855, 118341, 118828, 119316, 119805, 120295, 120786, 121278, 121771, 122265, 122760, 123256, 123753, 124251, 124750, 125250, 125751, 126253, 126756, 127260, 127765, 128271, 128778, 129286, 129795, 130305, 130816, 131328, 131841, 132355, 132870, 133386, 133903, 134421, 134940, 135460, 135981, 136503, 137026, 137550, 138075, 138601, 139128, 139656, 140185, 140715, 141246, 141778, 142311, 142845, 143380, 143916, 144453, 144991, 145530, 146070, 146611, 147153, 147696, 148240, 148785, 149331, 149878, 150426, 150975, 151525, 152076, 152628, 153181, 153735, 154290, 154846, 155403, 155961, 156520, 157080, 157641, 158203, 158766, 159330, 159895, 160461, 161028, 161596, 162165, 162735, 163306, 163878, 164451, 165025, 165600, 166176, 166753, 167331, 167910, 168490, 169071, 169653, 170236, 170820, 171405, 171991, 172578, 173166, 173755, 174345, 174936, 175528, 176121, 176715, 177310, 177906, 178503, 179101, 179700, 180300, 180901, 181503, 182106, 182710, 183315, 183921, 184528, 185136, 185745, 186355, 186966, 187578, 188191, 188805, 189420, 190036, 190653, 191271, 191890, 192510, 193131, 193753, 194376, 195000, 195625, 196251, 196878, 197506, 198135, 198765, 199396, 200028, 200661, 201295, 201930, 202566, 203203, 203841, 204480, 205120, 205761, 206403, 207046, 207690, 208335, 208981, 209628, 210276, 210925, 211575, 212226, 212878, 213531, 214185, 214840, 215496, 216153, 216811, 217470, 218130, 218791, 219453, 220116, 220780, 221445, 222111, 222778, 223446, 224115, 224785, 225456, 226128, 226801, 227475, 228150, 228826, 229503, 230181, 230860, 231540, 232221, 232903, 233586, 234270, 234955, 235641, 236328, 237016, 237705, 238395, 239086, 239778, 240471, 241165, 241860, 242556, 243253, 243951, 244650, 245350, 246051, 246753, 247456, 248160, 248865, 249571, 250278, 250986, 251695, 252405, 253116, 253828, 254541, 255255, 255970, 256686, 257403, 258121, 258840, 259560, 260281, 261003, 261726, 262450, 263175, 263901, 264628, 265356, 266085, 266815, 267546, 268278, 269011, 269745, 270480, 271216, 271953, 272691, 273430, 274170, 274911, 275653, 276396, 277140, 277885, 278631, 279378, 280126, 280875, 281625, 282376, 283128, 283881, 284635, 285390, 286146, 286903, 287661, 288420, 289180, 289941, 290703, 291466, 292230, 292995, 293761, 294528, 295296, 296065, 296835, 297606, 298378, 299151, 299925, 300700, 301476, 302253, 303031, 303810, 304590, 305371, 306153, 306936, 307720, 308505, 309291, 310078, 310866, 311655, 312445, 313236, 314028, 314821, 315615, 316410, 317206, 318003, 318801, 319600, 320400, 321201, 322003, 322806, 323610, 324415, 325221, 326028, 326836, 327645, 328455, 329266, 330078, 330891, 331705, 332520, 333336, 334153, 334971, 335790, 336610, 337431, 338253, 339076, 339900, 340725, 341551, 342378, 343206, 344035, 344865, 345696, 346528, 347361, 348195, 349030, 349866, 350703, 351541, 352380, 353220, 354061, 354903, 355746, 356590, 357435, 358281, 359128, 359976, 360825, 361675, 362526, 363378, 364231, 365085, 365940, 366796, 367653, 368511, 369370, 370230, 371091, 371953, 372816, 373680, 374545, 375411, 376278, 377146, 378015, 378885, 379756, 380628, 381501, 382375, 383250, 384126, 385003, 385881, 386760, 387640, 388521, 389403, 390286, 391170, 392055, 392941, 393828, 394716, 395605, 396495, 397386, 398278, 399171, 400065, 400960, 401856, 402753, 403651, 404550, 405450, 406351, 407253, 408156, 409060, 409965, 410871, 411778, 412686, 413595, 414505, 415416, 416328, 417241, 418155, 419070, 419986, 420903, 421821, 422740, 423660, 424581, 425503, 426426, 427350, 428275, 429201, 430128, 431056, 431985, 432915, 433846, 434778, 435711, 436645, 437580, 438516, 439453, 440391, 441330, 442270, 443211, 444153, 445096, 446040, 446985, 447931, 448878, 449826, 450775, 451725, 452676, 453628, 454581, 455535, 456490, 457446, 458403, 459361, 460320, 461280, 462241, 463203, 464166, 465130, 466095, 467061, 468028, 468996, 469965, 470935, 471906, 472878, 473851, 474825, 475800, 476776, 477753, 478731, 479710, 480690, 481671, 482653, 483636, 484620, 485605, 486591, 487578, 488566, 489555, 490545, 491536, 492528, 493521, 494515, 495510, 496506, 497503, 498501
};