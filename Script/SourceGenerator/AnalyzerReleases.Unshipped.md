### Dynamic Rules

| Rule ID    | Category     | Severity | Notes                                                                                                                                                                 |
|------------|--------------|----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| UC_ERROR_01 | UnrealCSharp | Error    | The partial keyword must be added to the dynamic class/dynamic struct to ensure that the source generator adds the necessary code to the dynamic class/dynamic struct |
| UC_ERROR_02 | UnrealCSharp | Error    | The file name where the dynamic class and dynamic struct are located must be consistent with the class name (excluding A, U, or F) |
| UC_ERROR_03 | UnrealCSharp | Error    | Dynamic classes inherited from blueprints must end with "_C", dynamic AActor classes inherited from C++ must start with "A" or end with "_C", dynamic non Actor classes inherited from C++ must start with "U" or end with "_C", and dynamic structures must start with "F" |
| UC_ERROR_04 | UnrealCSharp | Error    | UClass must have a base class |
| UC_ERROR_05 | UnrealCSharp | Error    | Type must be unique |
| UC_ERROR_06 | UnrealCSharp | Error    | UFunction must be unique |
| UC_ERROR_07 | UnrealCSharp | Error    | UProperty must be unique |
| UC_ERROR_08 | UnrealCSharp | Error    | Sealed event cannot be overridden |
