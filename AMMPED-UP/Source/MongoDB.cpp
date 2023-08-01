#include "../Header Files/MongoDB.h"
std::vector<std::string> getDatabases(mongocxx::client& client)
{
	std::vector<std::string> cldn = client.list_database_names();
	return cldn;
}
learning::MongoDB::MongoDB()
	//api(mongocxx::options::server_api::version::k_version_1)
{
		//client_options.server_api_opts(api);
		conn = mongocxx::client(mongoURI);
		if (conn)
		{
			std::cout << "Passed" << std::endl;
		}
		else
		{
			std::cout << "Failed" << std::endl;
		}
		
		std::cout << "database access is about to start" << std::endl;

		//ammpedUPDB = conn.database(dbName);
		//std::cout << "conn is done";
		//loginInfoCollection = ammpedUPDB.collection(collName);

		ammpedUPDB = conn["ammped-upDB"];
		std::cout << "database access is done" << std::endl;
		loginInfoCollection = ammpedUPDB["LoginInfo"];
		if (loginInfoCollection)
		{

			std::cout << "collection is also done" << std::endl;
			std::cout << loginInfoCollection.name() << std::endl;
		}
}

void learning::MongoDB::insertDocument(const bsoncxx::document::value document)
{
	loginInfoCollection.insert_one(document.view());
}

std::tuple<std::string, std::string, std::string> learning::MongoDB::findDocument(const std::string& value)
{
	std::cout << "inside findDocument func" << std::endl;

	std::string key;
	if (value.find('@') != std::string::npos) {
		// Contains '@' symbol, so it looks like an email
		key = "email";
	}
	else {
		// Doesn't contain '@', so it looks like a username
		key = "username";
	}
	std::cout << key + " finding key has been set" << std::endl;
	//auto cursor_all = loginInfoCollection.find({});
	
	find_one_filtered_result = loginInfoCollection.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp(key, value)));

	//auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
	std::cout << "filter has been created depending on the key" << std::endl;

	// Add query filter argument in find
	//auto cursor = loginInfoCollection.find({ filter });
	std::cout << "filter has been added to find the desired query result" << std::endl;
	
	if (!find_one_filtered_result) {
		std::cout << "query was not found" << std::endl;

		return  { "", "", "" };; // No data found
	}
	std::cout << "query is found" << std::endl;

	// Extract the first document from the cursor
	//auto document = *cursor.begin();
	auto document = *find_one_filtered_result;
	std::cout << "extracted the data from the query" << std::endl;

	// Extract the individual components of the retrieved data
	std::string retrievedUsername = std::string(document["username"].get_string().value);
	std::string retrievedEmail = std::string(document["email"].get_string().value);
	std::string retrievedPassword = std::string(document["pwd"].get_string().value);
	std::cout << "indiividual data has been extracted" << std::endl;

	return  { retrievedUsername, retrievedEmail, retrievedPassword };
}

bool learning::MongoDB::isDataPresent(const std::string& key, const std::string& value)
{
	// Create the query filter
	auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
	// Add query filter argument in find
	auto cursor = loginInfoCollection.find({ filter });
	return (cursor.begin() != cursor.end());
}

int learning::MongoDB::findScore(const std::string& value)
{
	auto filter = bsoncxx::builder::stream::document{} << "username" << value << bsoncxx::builder::stream::finalize;
	mongocxx::options::find opts;
	opts.projection(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("score", 1)));
	auto cursor = loginInfoCollection.find({ filter }, opts);
	for (auto&& doc : cursor)
	{
		bsoncxx::document::element curvename = doc["score"];
		int score = curvename.get_int32().value;
		return score;
	}
}

void learning::MongoDB::updateDocument(const std::string& key, const int& value, const std::string& newKey, const int& newValue)
{
	loginInfoCollection.update_one(bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize,
		bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << newKey << newValue << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize);
}

std::vector<std::pair<std::string, int>> learning::MongoDB::getTopScores(int limit)
{
	std::vector<std::pair<std::string, int>> topScores;
	mongocxx::options::find opts;
	opts.sort(bsoncxx::builder::basic::make_document(
		bsoncxx::builder::basic::kvp("score", -1)));
	opts.limit(limit);
	auto cursor = loginInfoCollection.find({}, opts);
	for (auto&& doc : cursor) {
		std::string username = std::string(doc["username"].get_string().value);
		int score = doc["score"].get_int32().value;

		topScores.emplace_back(username, score);
	}
	return topScores;
}