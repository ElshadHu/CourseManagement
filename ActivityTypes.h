//the main purpose of optional and type traits is that via type traits i can be sure the tpye is enum in worst case scenario  i will not send back the ugly pointer or different errors
//i will send the std::optional <E> means that either i got an  enum or nothing matched

// ActivityTypes.h
#pragma once
#include <string_view>
#include <array>
#include <utility>
#include <type_traits>
#include <optional>

namespace activities{

    enum class ActivityType { Assignment, Test, Quiz, Attendance, Discussion };
    enum class Grade { A,B,C,D,F,Incomplete,Withdrawn };
    enum class AttendanceStatus { P, A, L, MA, FE, FT };
    //Traits
    template<typename E>
    struct EnumTraits;//primary template no definition

    //template for ActivityType
    template<>
    struct EnumTraits<ActivityType>{
        static constexpr std::array<std::pair<ActivityType,std::string_view>,5>map{{
                 std::make_pair(ActivityType::Assignment, "Assignment"),
                std::make_pair(ActivityType::Test,     "Test"),
                std::make_pair(ActivityType::Quiz,     "Quiz"),
                std::make_pair(ActivityType::Attendance, "Attendance"),
                std::make_pair(ActivityType::Discussion, "Discussion"),
           }};
    };

//Grading mapping
    template<>
    struct EnumTraits<Grade>{
        static constexpr std::array<std::pair<Grade,std::string_view>,7>map{{
            std::make_pair(Grade::A,"A"),
            std::make_pair(Grade::B,"B"),
            std::make_pair(Grade::C,"C"),
             std::make_pair(Grade::D,"D"),
             std::make_pair(Grade::F,"F"),
            std::make_pair(Grade::Incomplete,"Incomplete"),
             std::make_pair(Grade::Withdrawn,"Withdrawn"),
        }}  ;

    };


    // AttendanceStatus mapping
    template <>
    struct EnumTraits<AttendanceStatus> {
        static constexpr std::array<std::pair<AttendanceStatus, std::string_view>, 6> map{{
            {AttendanceStatus::P, "P"},
            {AttendanceStatus::A, "A"},
            {AttendanceStatus::L, "L"},
            {AttendanceStatus::MA, "MA"},
            {AttendanceStatus::FE, "FE"},
            {AttendanceStatus::FT, "FT"},
        }};
    };
    template<typename E>
    constexpr std::string_view to_string(E e) {
        static_assert(std::is_enum_v<E>, "to_string requires an enum");
        for (auto&& m : EnumTraits<E>::map) {
            if (m.first == e) return m.second;   // enum -> string
        }
        return "Unknown";
    }

    template <typename E>
    constexpr std::optional<E> from_string(std::string_view s) {
        static_assert(std::is_enum_v<E>, "from_string requires an enum");
        for (auto&& m : EnumTraits<E>::map) {
            if (m.second == s) return m.first;   // string -> enum
        }
        return std::nullopt;
    }


}


