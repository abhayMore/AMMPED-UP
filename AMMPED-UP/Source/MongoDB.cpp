#include "../Header Files/MongoDB.h"
std::vector<std::string> getDatabases(mongocxx::client& client)
{
	std::vector<std::string> cldn = client.list_database_names();
	return cldn;
}
learning::MongoDB::MongoDB() :instance(MongoInstance::getInstance()),
	api(mongocxx::options::server_api::version::k_version_1)
{
	connect();
	//ammpedUPDB = conn.database(dbName);
	//std::cout << "conn is done";
	//loginInfoCollection = ammpedUPDB.collection(collName);	
}

void learning::MongoDB::connect()
{
	try
	{
		client_options.server_api_opts(api);
		conn = mongocxx::client(mongoURI, client_options);
		ammpedUPDB = conn.database(bsoncxx::string::view_or_value(dbName));
		loginInfoCollection = ammpedUPDB.collection(bsoncxx::string::view_or_value(collName));
		const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
		ammpedUPDB.run_command(ping_cmd.view());
		std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl;
	}
	catch (const std::exception& e)
	{
		// Handle errors.
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void learning::MongoDB::insertDocument(const bsoncxx::document::value document)
{
	loginInfoCollection.insert_one(document.view());
}

std::tuple<std::string, std::string, std::string> learning::MongoDB::findDocument(const std::string& value)
{

	std::string key;
	if (value.find('@') != std::string::npos) {
		// Contains '@' symbol, so it looks like an email
		key = "email";
	}
	else {
		// Doesn't contain '@', so it looks like a username
		key = "username";
	}
	//auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
	//auto cursor_all = loginInfoCollection.find({});

	find_one_filtered_result = loginInfoCollection.find_one(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp(key, value)));
	// Add query filter argument in find
	//auto cursor = loginInfoCollection.find({ filter });
	
	if (!find_one_filtered_result) {
		return  { "", "", "" };; // No data found
	}

	// Extract the first document from the cursor
	//auto document = *cursor.begin();
	auto &document = *find_one_filtered_result;

	// Extract the individual components of the retrieved data
	std::string retrievedUsername = std::string(document["username"].get_string().value);
	std::string retrievedEmail = std::string(document["email"].get_string().value);
	std::string retrievedPassword = std::string(document["pwd"].get_string().value);

	return  { retrievedUsername, retrievedEmail, retrievedPassword };
}

bool learning::MongoDB::isDataPresent(const std::string& key, const std::string& value)
{
	// Create the query filter
	bsoncxx::v_noabi::document::value filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
	// Add query filter argument in find
	mongocxx::v_noabi::cursor cursor = loginInfoCollection.find(filter.view());
	return (cursor.begin() != cursor.end());
}

int learning::MongoDB::findScore(const std::string& value)
{
	bsoncxx::v_noabi::document::value filter = bsoncxx::builder::stream::document{} << "username" << value << bsoncxx::builder::stream::finalize;
	mongocxx::options::find opts;
	opts.projection(bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("score", 1)));
	mongocxx::v_noabi::cursor cursor = loginInfoCollection.find(filter.view(), opts);
	for (auto&& doc : cursor)
	{
		bsoncxx::document::element curvename = doc["score"];
		int score = curvename.get_int32().value;
		return score;
	}
	return 0;
}

//void learning::MongoDB::updateDocument(const std::string & userName, const std::string& key, const int& value, const std::string& newKey, const int& newValue)
void learning::MongoDB::updateDocument(const std::string& userName, const std::string& key, const int& value)
{
	bsoncxx::builder::stream::document filter_builder{};
	filter_builder << "username" << userName;

	bsoncxx::builder::stream::document update_builder{};
	update_builder << "$set" << bsoncxx::builder::stream::open_document << key << value << bsoncxx::builder::stream::close_document;
	loginInfoCollection.update_one(filter_builder.view(), update_builder.view());
	
	//loginInfoCollection.update_one(bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize, bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << newKey << newValue << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize);
}

int learning::MongoDB::getDocumentCount()
{
	bsoncxx::builder::basic::document filter_builder{}; // Optionally, you can provide a filter
	return static_cast<int>(loginInfoCollection.count_documents(filter_builder.view()));
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

bool learning::MongoDB::getConnection()
{
	//connect();
	return conn ? true : false;
}
