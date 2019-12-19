import Foundation


func getCurrentDate() -> String {
    let date = Date()
    let calendar = Calendar.current
    let day = calendar.component(.day, from: date)
    let month = calendar.component(.month, from: date)
    let year = calendar.component(.year, from: date)
    let hour = calendar.component(.hour, from: date)
    let minutes = calendar.component(.minute, from: date)
    let seconds = calendar.component(.second, from: date)
    return "\(day).\(month).\(year)*\(hour):\(minutes):\(seconds)"
}


let sourceFolder = FileManager.default.currentDirectoryPath
let destFolder = "/Users/seryogas/Desktop"//FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
let currBackupFolderPathURL = URL(string: destFolder)!.appendingPathComponent("/MY_BACKUPS" + "/" + (sourceFolder + ":" + getCurrentDate()).replacingOccurrences(of: "/", with: "->", options: .literal, range: nil))
print(currBackupFolderPathURL.path)