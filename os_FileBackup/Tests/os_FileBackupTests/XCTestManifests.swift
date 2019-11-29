import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(os_FileBackupTests.allTests),
    ]
}
#endif
