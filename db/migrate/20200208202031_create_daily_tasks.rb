class CreateDailyTasks < ActiveRecord::Migration[6.0]
  def change
    create_table :daily_tasks do |t|
      t.references :user, null: false, foreign_key: true
      t.references :task, null: false, foreign_key: true
      t.boolean :complete

      t.timestamps
    end
  end
end
