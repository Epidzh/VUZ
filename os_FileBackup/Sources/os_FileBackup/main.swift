import Foundation


let backupURL = "/Users/seryogasx/Desktop"
let o = "kek"
let fileManager = FileManager.default
do {
    try fileManager.createDirectory(atPath: o, withIntermediateDirectories: false)
}
catch let error {
    print("OOOOOPS!!: \(error)")
}

do {
    let items = try fileManager.contentsOfDirectory(atPath: ".")
    for i in items {
        try fileManager.copyItem(atPath: "./\(i)", toPath: backupURL)
    }
    print(items)
}
catch let error {
    print("OOOOOPS!!: \(error)")
}