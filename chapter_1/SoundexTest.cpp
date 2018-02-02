#include "gmock/gmock.h" 

#include "Soundex.h"

using namespace testing;

class SoundexEncoding: public Test {
public:
   Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
   ASSERT_THAT(soundex.encode("A"), Eq("A000")); 
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
   ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
   EXPECT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
	ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonantsWithDigits) {
	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
	ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
	ASSERT_THAT(soundex.encode("BaAeEiIoOuUhycdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {

	ASSERT_THAT(soundex.encodedDigit('b'), soundex.encodedDigit('f'));
	ASSERT_THAT(soundex.encodedDigit('c'), soundex.encodedDigit('g'));
	ASSERT_THAT(soundex.encodedDigit('d'), soundex.encodedDigit('t'));

	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercaseFirstLetter) {
	ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
	ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombineDuplicateCodesWhen2ndLetterDuplicates1st) {
	ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
	ASSERT_THAT(soundex.encode("Jbob"), Eq("J110"));
}